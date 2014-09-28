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

#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"


#define FIRST_SCENE Home

//To use the testflight SDK, enter a token
//#define TESTFLIGHT_TOKEN @""

//Debug analytics have a different ID and are on a separate app on Flurry. Put at 0 for release
#define DEBUG_ANALYTICS 1

//Display stats about performance in the lower left corner : fps, number of cocos objects and time for a frame. Put at false for release
#define DISPLAY_PERF_STATS true

//The build version that will be printed to the lower right, using only alpha-numeric caracters and no quotes
//It is shown with DISPLAY_PERF_STATS
#define BUILD_VERSION Dev

//Double-expansion stringifaction macro trick for BUILD_VERSION
#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

//Force the images to be picked from the library, to avoid the choice of photo/library. Put at 0 for release
#define FORCE_LIBRARY 0

#define USE_TRANSLATION 1

//Verbose is used to put on or off certain CCLOG. Put all at 0 for release
//Warning : for events, you have to manually change it in CCNotificationCenter, since it's part of cocos2d

//Log every FenneX object dealloc. Useful to detect leaks
#define VERBOSE_DEALLOC 0

#define VERBOSE_WARNING 1

//Log load and save plist. Useful to detect uncorrectly formated plist
#define VERBOSE_SAVE_PLIST 0
#define VERBOSE_LOAD_PLIST 0

//Log CCB loading. Useful when the app crash during a scene switch to identify missing ressource
#define VERBOSE_LOAD_CCB 0

//Log localization queries. Useful when translating
#define VERBOSE_LOCALIZATION 0

//Log analytics (Flurry). Useful when it's not working properly
#define VERBOSE_ANALYTICS 0

//Log some performance time. Useful to detect bottlenecks when the app is too slow
#define VERBOSE_PERFORMANCE_TIME 1

//Log some general info to know where you are in the app. Useful for remote debugging
#define VERBOSE_GENERAL_INFO 0

//Log infos about touch recognizers. Useful when the detection is going nuts
#define VERBOSE_TOUCH_RECOGNIZERS 0

//Log infos about AudioPlayerRecorder
#define VERBOSE_AUDIO 1


/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_1024X768

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" }; //426x320 for ipad resolution
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };


#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(2048, 1536);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)

#define RESOLUTION_MULTIPLIER (CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width / designResolutionSize.width)

#endif /* __APPMACROS_H__ */
