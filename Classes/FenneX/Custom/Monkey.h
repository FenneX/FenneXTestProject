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

#ifndef __FenneX__Monkey__
#define __FenneX__Monkey__
#include "FenneXCore.h"
#include "SceneName.h"

/* Monkey's sole purpose is to tap everywhere on the screen. Tap, tap, tap, tap
   It's first goal is to try to navigate to all the scenes, it's the phase during which it will as much as possible target PlanSceneSwitch with Scenes not already visited
   After that, it will switch on somewhat random, tapping on every actionnable button possible
 */

typedef enum
{
    SearchScenes,
    Random
} MonkeyState;

#define MAX_SEARCH_ITERATIONS 100

USING_NS_FENNEX;

class Monkey : public CCObject, public Pausable
{
public:
    static Monkey* excitedMonkey(void);
    virtual void update(float delta);
protected:
    void init();
    MonkeyState state;
    int iterations;
    bool isSceneVisited[SCENES_NUMBER];
    void removeBadButtons(CCArray* buttons);
    CCArray* selectAllScenesSwitchButtons(CCArray* buttons);
    CCArray* selectUnknownScenesSwitchButtons(CCArray* buttons);
};

#endif /* defined(__FenneX__Monkey__) */
