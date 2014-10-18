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

#ifndef FenneX_SceneName_h
#define FenneX_SceneName_h

// TODO : Change this

//This file should contain only an enum with names of the different scenes
#define SCENES_NUMBER sizeof(SceneName)
typedef enum
{
	None = 0,
    SplashScreen = 1,
    Home = 2,
    TestImagePicker = 3,
}SceneName;

//Here is the place to put your hierarchy so FenneX know what to do with a Back event
static SceneName getPreviousSceneName(SceneName scene)
{
    switch(scene)
    {
        case TestImagePicker:
            return Home;
        default:
            return None;
    }
    return None;
}

//Allow auto-load of ccb files according their name and pretty print for analytics
static const char* formatSceneToString(SceneName scene)
{
	switch (scene)
	{
		case None:
			return "None";
		case SplashScreen:
			return "SplashScreen";
		case Home:
			return "Home";
		case TestImagePicker:
			return "TestImagePicker";
    }
    return "Missing From List";
}

#endif
