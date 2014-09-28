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

#include "Logs.h"
#include "AppDelegate.h"
#include "AppMacros.h"
#include "editor-support/cocosbuilder/CocosBuilder.h"
#include "FenneXCore.h"
#include "FenneXWrappers.h"
#include <vector>
#include <string>

using namespace std;
USING_NS_CC;


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::loadAnalytics()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    AnalyticsWrapper::setAppVersion("0.1");
    CCLOG("Set iOS app version");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AnalyticsWrapper::setAppVersion("0.1");
    CCLOG("Set Android app version");
#endif
    
#if DEBUG_ANALYTICS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    AnalyticsWrapper::GAStartSession("YOUR-GA-KEY");
    AnalyticsWrapper::flurryStartSession("YOUR-FLURRY-KEY");
    CCLOG("start flurry iOS debug session");
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AnalyticsWrapper::GAStartSession("YOUR-GA-KEY");
    AnalyticsWrapper::flurryStartSession("YOUR-FLURRY-KEY");
    CCLOG("start flurry Android debug session");
#endif
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    AnalyticsWrapper::GAStartSession("YOUR-GA-KEY");
    AnalyticsWrapper::flurryStartSession("YOUR-FLURRY-KEY");
    CCLOG("start flurry iOS release session");
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AnalyticsWrapper::GAStartSession("YOUR-GA-KEY");
    AnalyticsWrapper::flurryStartSession("YOUR-FLURRY-KEY");
    CCLOG("start flurry Android release session");
#endif
#endif
    AnalyticsWrapper::setDebugLogEnabled(VERBOSE_ANALYTICS);
}

void AppDelegate::initAppModules()
{
    //The scene switcher have to be initialized BEFORE most things (to get PlanSceneSwitch event before)
    SceneSwitcher::sharedSwitcher();
    //Disable pop up notify for fail (for example at resume, it will try to load some delete assets if you remove a custom photo
    CCFileUtils::sharedFileUtils()->setPopupNotify(false);
    
	CCDictionary* settings = (CCDictionary*)loadObjectFromFile("last_settings.plist");
	bool firstLaunch = settings == NULL || !isKindOfClass(settings->objectForKey("FirstLaunch"), CCBool) || TOBOOL(settings->objectForKey("FirstLaunch"));
	if(firstLaunch)
	{
		CCString* language = ScreateF("Language: %s", getLocalLanguage());
		if(settings == NULL)
		{
			settings = Dcreate();
		}
		CCLOG("%s", language->getCString());
		AnalyticsWrapper::logEvent(language->getCString());
		settings->setObject(Screate(getLocalLanguage()), "Language");
		settings->setObject(Bcreate(false), "FirstLaunch");
	}
	else if(strcmp(getLocalLanguage(), TOCSTRING(settings->objectForKey("Language"))) != 0)
	{
		CCString* language = ScreateF("Change to language: %s, previous language: %s", getLocalLanguage(), TOCSTRING(settings->objectForKey("Language")));
		CCLOG("%s", language->getCString());
		AnalyticsWrapper::logEvent(language->getCString());
		settings->setObject(Screate(getLocalLanguage()), "Language");
	}
	saveObjectToFile(settings, "last_settings.plist");
    
    //Initialize Audio session (not in recording mode at startup)
	AudioPlayerRecorder::sharedRecorder();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	vector<string> searchPath;

	loadAnalytics();
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCDirector::sharedDirector()->getOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
	CCSize frameSize = pEGLView->getFrameSize();
    // Set the design resolution
    pEGLView->setDesignResolutionSize(frameSize.width, frameSize.height, kResolutionShowAll);

    //Default advised settings for ipadhd(100%)/ipad(50%)/iphone(21%)
    // if the frame's height is larger than the height of medium resource size, select large resource.
    // the selection is done using preset values to have the best directory selected on every tablet (for example, ipad retina size on 1280x800 isn't a good option)
	if (frameSize.width > 1280 && frameSize.height > 800)
	{ 
		searchPath.push_back(largeResource.directory);
        CCBReader::setResolutionScale(1/MAX(largeResource.size.width/frameSize.width, largeResource.size.height/frameSize.height));
        CCBLoaderSetScale(MIN(largeResource.size.width/designResolutionSize.width, largeResource.size.height/designResolutionSize.height));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.width > 640 && frameSize.height > 480)
    {
        searchPath.push_back(mediumResource.directory);
        CCBReader::setResolutionScale(1/MAX(mediumResource.size.width/frameSize.width, mediumResource.size.height/frameSize.height));
        CCBLoaderSetScale(MIN(mediumResource.size.width/designResolutionSize.width, mediumResource.size.height/designResolutionSize.height));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    { 
		searchPath.push_back(smallResource.directory);
        CCBReader::setResolutionScale(1/MAX(smallResource.size.width/frameSize.width, smallResource.size.height/frameSize.height));
        CCBLoaderSetScale(MIN(smallResource.size.width/designResolutionSize.width, smallResource.size.height/designResolutionSize.height));
    }
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    //If it's a phone, CCBLoader will automatically try to load ccb finishing by -phone first
    CCBLoaderSetPhoneLayout(isPhone());
    CCLog("Scale factor for director : %f, for CCBReader : %f, resolution : %f, %f, resource directory : %s", pDirector->getContentScaleFactor(), CCBReader::getResolutionScale(), frameSize.width, frameSize.height, searchPath[0].c_str());
	
    // turn on display FPS
#ifdef BUILD_VERSION
    pDirector->setDisplayStatsWithBuild(DISPLAY_PERF_STATS, STRINGIFY(BUILD_VERSION));
#else
    pDirector->setDisplayStats(DISPLAY_PERF_STATS);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //Run the first scene. On Android, show a custom splashscreen during app modules init. On iOS, the splashscreen will be shown during first frame loading
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    SceneSwitcher::sharedSwitcher()->initWithScene(SplashScreen);
    AppDelegate::initAppModules();
#else
    AppDelegate::initAppModules();
    SceneSwitcher::sharedSwitcher()->initWithScene(FIRST_SCENE);
#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCNotificationCenter::sharedNotificationCenter()->postNotification("AppEnterBackground");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("Stopping flurry session on enter background");
    AnalyticsWrapper::endSession();
#endif
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("Starting flurry session on enter foreground");
    loadAnalytics();
#endif
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::applicationDidReceiveMemoryWarning()
{
    CCLOG("Removing unused textures ...");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCLOG("Unused textures removed!");
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}