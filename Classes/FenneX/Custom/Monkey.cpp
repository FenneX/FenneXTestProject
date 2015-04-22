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

#include "Monkey.h"

static Monkey *s_Monkey = NULL;

Monkey* Monkey::excitedMonkey(void)
{
    if (!s_Monkey)
    {
        s_Monkey = new Monkey();
        s_Monkey->init();
    }
    
    return s_Monkey;
}

void Monkey::update(float delta)
{
    if(state == SearchScenes)
    {
        isSceneVisited[SceneSwitcher::sharedSwitcher()->getCurrentSceneName()] = true;
        bool searchFinished = true;
        for(int i = 0; i < SCENES_NUMBER && searchFinished; i++)
        {
            if(!isSceneVisited[i])
            {
                searchFinished = false;
            }
        }
        if(searchFinished)
        {
            state = Random;
        }
    }
    CCArray* buttons = GraphicLayer::sharedLayer()->allActionnableObjects();
    this->removeBadButtons(buttons);
    CCArray* probableTargets = NULL;
    if(state == SearchScenes)
    {
        probableTargets = this->selectUnknownScenesSwitchButtons(buttons);
        if(probableTargets->count() == 0)
        {
            probableTargets = this->selectAllScenesSwitchButtons(buttons);
        }
        if(probableTargets->count() == 0)
        {
            probableTargets = buttons;
        }
    }
    else
    {
        probableTargets = buttons;
    }
    if(probableTargets->count() != 0)
    {
        RawObject* target = (RawObject*)probableTargets->objectAtIndex(arc4random()%probableTargets->count());
        GraphicLayer::sharedLayer()->touchAtPosition(GraphicLayer::sharedLayer()->getRealPosition(target), true);
    }
    iterations++;
    if(state == SearchScenes && iterations > MAX_SEARCH_ITERATIONS)
    {
        state = Random;
    }
}

void Monkey::init()
{
    state = SearchScenes;
    iterations = 0;
    isSceneVisited[0] = true;//None can't be visited
    for(int i = 1; i < SCENES_NUMBER; i++)
    {
        isSceneVisited[i] = false;
    }
}

void Monkey::removeBadButtons(CCArray* buttons)
{
    CCRect windowRect = CCRectMake(0, 0, CCDirector::sharedDirector()->getWinSize().width, CCDirector::sharedDirector()->getWinSize().height);
    GraphicLayer* layer = GraphicLayer::sharedLayer();
    for(int i = buttons->count() - 1; i >= 0; i--)
    {
        RawObject* obj = (RawObject*)buttons->objectAtIndex(i);
        //Remove objects which don't collide with windowRect. It uses code from CCRect::intersectRect (which can't be used directly because a CCRect origin must be > (0,0))
        CCPoint pos = layer->getRealPosition(obj);
        CCSize size = SizeMult(obj->getSize(), layer->getRealScale(obj));
        if(windowRect.getMaxX() < pos.x - obj->getNode()->getAnchorPoint().x * size.width ||
           pos.x + (1-obj->getNode()->getAnchorPoint().x) * size.width <      windowRect.getMinX() ||
           windowRect.getMaxY() < pos.y - obj->getNode()->getAnchorPoint().y * size.height ||
           pos.y + (1-obj->getNode()->getAnchorPoint().y) * size.height <      windowRect.getMinY())
        {
            buttons->removeObject(obj);
        }
        else if(obj->getEventName() == "PickImage"
           || obj->getEventName() == "OpenKeyboard"
           || obj->getEventName() == "DoNothing"
           )
        {
            buttons->removeObject(obj);
        }
    }
}

CCArray* Monkey::selectAllScenesSwitchButtons(CCArray* buttons)
{
    CCArray* result = Acreate();
    for(int i = 0; i < buttons->count(); i++)
    {
        RawObject* obj = (RawObject*)buttons->objectAtIndex(i);
        if(obj->getEventName() == "PlanSceneSwitch")
        {
            result->addObject(obj);
        }
    }
    return result;    
}

CCArray* Monkey::selectUnknownScenesSwitchButtons(CCArray* buttons)
{
    CCArray* result = Acreate();
    for(int i = 0; i < buttons->count(); i++)
    {
        RawObject* obj = (RawObject*)buttons->objectAtIndex(i);
        if(obj->getEventName() == "PlanSceneSwitch"
           && !isSceneVisited[TOINT(obj->getEventInfos()->objectForKey("Scene"))])
        {
            result->addObject(obj);
        }
    }
    return result;
}
