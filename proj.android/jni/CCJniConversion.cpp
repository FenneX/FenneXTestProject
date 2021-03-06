/****************************************************************************
Copyright (c) 2013-2014 Auticiel SAS

http://www.fennex.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************///

#include "CCJniConversion.h"

USING_NS_FENNEX;

#define VERBOSE_JNI_CONVERSION 0

jobjectArray jobjectArrayFromCCDictionary(JNIEnv *pEnv, CCDictionary * ccDictionary)
{
#if VERBOSE_JNI_CONVERSION
	CCLOG("converting CCDictionary to native array ....");
#endif
    if (ccDictionary == NULL)
    {
        return NULL;
    }
    else if (ccDictionary->allKeys() == NULL)
    {
        return NULL;
    }
    else if (ccDictionary->allKeys()->count() <= 0)
    {
        return NULL;
    }
            
    jclass jStringCls = 0;
        
    jStringCls = pEnv->FindClass("java/lang/String");
	if(pEnv->ExceptionCheck())
	{
		pEnv->ExceptionDescribe();
		CCLOG("crashed when looking for String Class");
		return NULL;
	}
        
    jobjectArray result;
        
    result = pEnv->NewObjectArray( 2 * ccDictionary->allKeys()->count(), jStringCls, NULL);

	if(pEnv->ExceptionCheck())
	{
		pEnv->ExceptionDescribe();
		CCLOG("crashed when creating array");
	}
    if (result == NULL) {
        CCLog("failed to create a new jobjectArray");
        return NULL;
    }
    
    for (int i = 0; i < ccDictionary->allKeys()->count(); i++) {

    	CCString* objToString;
    	CCObject* obj = ccDictionary->objectForKey(((CCString*)ccDictionary->allKeys()->objectAtIndex(i))->getCString());
        if(isKindOfClass(obj, CCDictionary))
        {
        	objToString = Screate("Dictionary");
        }
        else if(isKindOfClass(obj, CCArray))
        {
        	objToString = Screate("Array");
        }
        else if (isKindOfClass(obj, CCString))
        {
            objToString = (CCString*)obj;
        }
        else if (isKindOfClass(obj, CCInteger))
        {
        	objToString = ScreateF("%d", TOINT(obj));
        }
        else if (isKindOfClass(obj, CCFloat))
        {
        	objToString = ScreateF("%f", TOFLOAT(obj));
        }
        else if (isKindOfClass(obj, CCBool))
        {
        	objToString = ScreateF("%s", TOBOOL(obj) ? "true" : "false");
        }

        jstring keyString = pEnv->NewStringUTF(((CCString *)ccDictionary->allKeys()->objectAtIndex(i))->getCString());

        jstring objectString = pEnv->NewStringUTF(objToString->getCString());

#if VERBOSE_JNI_CONVERSION
        CCLOG("%s", ((CCString *)ccDictionary->allKeys()->objectAtIndex(i))->getCString());
#endif
        pEnv->SetObjectArrayElement(result, i * 2, keyString);
#if VERBOSE_JNI_CONVERSION
        CCLOG("%s", objToString->getCString());
#endif
        pEnv->SetObjectArrayElement(result, i * 2 + 1, objectString);

    }
#if VERBOSE_JNI_CONVERSION
    CCLOG("Converted!");
#endif
    return result;
}

jobjectArray jobjectArrayFromCCArray(JNIEnv *pEnv, CCArray * ccArray)
{
#if VERBOSE_JNI_CONVERSION
	CCLOG("converting CCArray to native array ....");
#endif
    if (ccArray == NULL) {
        return NULL;
    } else if (ccArray->count() <= 0) {
        return NULL;
    }

    jclass jStringCls = 0;

    jStringCls = pEnv->FindClass("java/lang/String");
	if(pEnv->ExceptionCheck())
	{
		pEnv->ExceptionDescribe();
		CCLOG("crashed when looking for String Class");
		return NULL;
	}

    jobjectArray result;

    result = pEnv->NewObjectArray( ccArray->count(), jStringCls, NULL);

	if(pEnv->ExceptionCheck())
	{
		pEnv->ExceptionDescribe();
		CCLOG("crashed when creating array");
	}
    if (result == NULL) {
        CCLog("failed to create a new jobjectArray");
        return NULL;
    }

    for (int i = 0; i < ccArray->count(); i++) {

    	CCString* objToString;
    	CCObject* obj = ccArray->objectAtIndex(i);
        if(isKindOfClass(obj, CCDictionary))
        {
        	objToString = Screate("Dictionary");
        }
        else if(isKindOfClass(obj, CCArray))
        {
        	objToString = Screate("Array");
        }
        else if (isKindOfClass(obj, CCString))
        {
            objToString = (CCString*)obj;
        }
        else if (isKindOfClass(obj, CCInteger))
        {
        	objToString = ScreateF("%d", TOINT(obj));
        }
        else if (isKindOfClass(obj, CCFloat))
        {
        	objToString = ScreateF("%f", TOFLOAT(obj));
        }
        else if (isKindOfClass(obj, CCBool))
        {
        	objToString = ScreateF("%s", TOBOOL(obj) ? "true" : "false");
        }

        jstring objectString = pEnv->NewStringUTF(objToString->getCString());
#if VERBOSE_JNI_CONVERSION
        CCLOG("%s", objToString->getCString());
#endif
        pEnv->SetObjectArrayElement(result, i, objectString);
    }
#if VERBOSE_JNI_CONVERSION
    CCLOG("Converted!");
#endif
    return result;
}

typedef enum
{
	IntegerType,
	FloatType,
	BooleanType,
	StringType,
	NoType
}ConvertTypeInfo;

CCObject* CCObjectFromString(const char* string)
{
	CCObject* result = NULL;
	ConvertTypeInfo resolvedType = NoType;
	bool found = false;
	if(strlen(string) > 5)
	{
		found = true;
		if(strncmp(string, "[Str]", 5) == 0)
		{
			resolvedType = StringType;
		}
		else if(strncmp(string, "[Int]", 5) == 0)
		{
			resolvedType = IntegerType;
		}
		else if(strncmp(string, "[Flo]", 5) == 0)
		{
			resolvedType = FloatType;
		}
		else if(strncmp(string, "[Boo]", 5) == 0)
		{
			resolvedType = BooleanType;
		}
		else
		{
			found = false;
		}
		if(found)
		{
			string = std::string(string).substr(5, std::string::npos).c_str();
		}
	}
	if(resolvedType == BooleanType || (resolvedType == NoType &&  (strcmp(string, "true") == 0 || strcmp(string, "false") == 0)))
	{
		result = Bcreate(strcmp(string, "true") == 0);
	}
	else if(resolvedType == IntegerType || (resolvedType == NoType &&  (atoi(string) != 0 || strcmp(string, "0") == 0)))
	{
		result = Icreate(atoi(string));
	}
	else if(resolvedType == FloatType || (resolvedType == NoType && atof(string) != 0))
	{
		result = Fcreate(atof(string));
	}
	else
	{
		result = Screate(string);
	}
	return result;
}

CCDictionary* CCDictionaryFromjobjectArray(JNIEnv *pEnv, jobjectArray array)
{
#if VERBOSE_JNI_CONVERSION
	CCLOG("Converting jobjectArray to CCDictionary ....");
#endif
	jsize count = 0;

	if(array == NULL)
	{
		CCLOG("jobjectArray is null.");
		return NULL;
	}
	count = pEnv->GetArrayLength(array);
	if(count <= 0) {
		CCLOG("jobjectArray is empty.");
		return NULL;
	}
	else if(count % 2 != 0)
	{
		CCLOG("The count is not even, last object will be left out");
		count--;
	}

	CCDictionary* myArray = new CCDictionary();
	myArray->autorelease();
	jboolean flag = false;

	for(int i = 0; i < count; i += 2) {
		//Run through the array, retrieve each type and set it in a CCDictionary
		jobject element = pEnv->GetObjectArrayElement(array, i);
		if(element != NULL) {
			jstring stringElement = (jstring)element;
			const char* key = pEnv->GetStringUTFChars(stringElement, &flag);

			jobject nextObjectElement = pEnv->GetObjectArrayElement(array, i+1);
			const char* nextElement = pEnv->GetStringUTFChars((jstring)nextObjectElement, &flag);
			myArray->setObject(CCObjectFromString(nextElement), key);
		}
	}
#if VERBOSE_JNI_CONVERSION
	CCLOG("Converted!");
#endif
	return myArray;
}

CCArray* CCArrayFromjobjectArray(JNIEnv *pEnv, jobjectArray array)
{
#if VERBOSE_JNI_CONVERSION
	CCLOG("Converting jobjectArray to CCArray ....");
#endif
	jsize count = 0;

	if(array == NULL)
	{
		CCLOG("jobjectArray is null.");
		return NULL;
	}
	count = pEnv->GetArrayLength(array);
	if(count <= 0) {
		CCLOG("jobjectArray is empty.");
		return NULL;
	}

	CCArray* myArray = new CCArray();
	myArray->autorelease();
	jboolean flag = false;

	for(int i = 0;i < count;i++)
	{
		//Run through the array, retrieve each type and set it in a CCArray
		jobject element = pEnv->GetObjectArrayElement(array, i);
		const char* string = pEnv->GetStringUTFChars((jstring)element, &flag);
		myArray->addObject(CCObjectFromString(string));
	}
#if VERBOSE_JNI_CONVERSION
	CCLOG("Converted!");
#endif
	return myArray;
}

