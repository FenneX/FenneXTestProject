//
//  TestImagePickerScene.cpp
//  FenneXTestProject
//
//  Created by François Dupayrat on 18/10/14.
//
//

#include "TestImagePickerScene.h"
#include "ImagePickerWrapper.h"
#include <errno.h>
#include <unistd.h>

USING_NS_FENNEX;

#define ADD_OBSERVER(func, notifName) (center->addObserver(this, callfuncO_selector(TestImagePickerScene::func), notifName, NULL))
TestImagePickerScene::TestImagePickerScene(SceneName identifier, CCDictionary* parameters) : Scene(identifier, parameters)
{
    //Add the observers to handle events
    NotificationCenter* center = NotificationCenter::sharedNotificationCenter();
    ADD_OBSERVER(pickImage, "PickImage");
    ADD_OBSERVER(onImagePicked, "ImagePicked");
}

void TestImagePickerScene::pickImage(Ref* obj)
{
    Dictionary* infos = (Dictionary*)obj;
    //Get the parameters of the event (set in CocosBuilder). identifier is the name of the target image to replace
    bool useCamera = TOBOOL(infos->objectForKey("useCamera"));
    const char* identifier = TOCSTRING(infos->objectForKey("identifier"));
    
    //Generate a file name according current time to avoid collisions
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime (&rawtime);
    const char* filename = ScreateF("TestImagePicker_%d-%02d-%02d_%02d.%02d.%02d", timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec)->getCString();
    
    GraphicLayer* layer = GraphicLayer::sharedLayer();
    //Use the real size of sender to tell which size we want the image
    RawObject* sender = layer->getById(TOINT(infos->objectForKey("Sender")));
    CCAssert(sender != NULL, "Problem in pick image : sender is invalid");
    int width = sender->getNode()->getContentSize().width * layer->getRealScale(sender);
    int height = sender->getNode()->getContentSize().height * layer->getRealScale(sender);
    
    //Launch pick image workflow
    pickImageFrom(filename, useCamera, width, height, identifier);
}

void TestImagePickerScene::onImagePicked(Ref* obj)
{
    //Replace the target with the image we just picked
    Dictionary* infos = (Dictionary*)obj;
    std::string filename = TOCSTRING(infos->objectForKey("Name"));
    std::string identifier = TOCSTRING(infos->objectForKey("Identifier"));
    GraphicLayer* layer = GraphicLayer::sharedLayer();
    
    //Replace the image texture and set it visible
    FenneX::Image* target = (FenneX::Image*)layer->firstObjectWithName(identifier);
    target->replaceTexture(getLocalPath(filename.c_str())->getCString(), true, true);
    localFiles.push_back(filename);
    target->getNode()->setVisible(true);
    
    //Hide the help label
    FenneX::LabelTTF* helpLabel = (FenneX::LabelTTF*)layer->firstObjectWithName((CCString*)target->getEventInfos()->objectForKey("helpLabel"));
    helpLabel->getNode()->setVisible(false);
}

void TestImagePickerScene::stop()
{
    for(std::string filename : localFiles)
    {
        int result = unlink(getLocalPath((filename + ".png").c_str())->getCString());
        if(result == 0)
        {
            CCLOG("photo %s removed successfully", filename.c_str());
        }
        else
        {
            CCLOG("Problem removing photo %s, error : %d", filename.c_str(), errno);
        }
    }
    localFiles.clear();
    Scene::stop();
}
