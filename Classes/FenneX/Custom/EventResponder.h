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

#ifndef __FenneX__EventResponder__
#define __FenneX__EventResponder__

#include "FenneXCore.h"

USING_NS_CC;
USING_NS_FENNEX;

NS_FENNEX_BEGIN
class LayoutHandler;
NS_FENNEX_END

//this class is owned by LayoutHandler, which will update its properties
class EventResponder : public Ref
{
public:
    void planSceneSwitch(CCObject* obj); //will log a pagview when there is a sceneswitch
    void keyBackClicked(CCObject* obj); //for Android only, will perform a back, or quit the app if there is no available back or if it's a double tap
    void back(CCObject* obj); //Will perform a back action. That's where you want to intercept back for specific cases  (for example, an unvalid form)
    void quitApp(CCObject* obj); //for Android only, will quit the app after cleaning up analytics
private:
    GraphicLayer* layer;
    FenneX::Scene* currentScene;
    friend class FenneX::LayoutHandler;
};

#endif /* defined(__FenneX__EventResponder__) */
