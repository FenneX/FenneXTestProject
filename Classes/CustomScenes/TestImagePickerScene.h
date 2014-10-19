//
//  TestImagePickerScene.h
//  FenneXTestProject
//
//  Created by François Dupayrat on 18/10/14.
//
//

#ifndef __FenneXTestProject__TestImagePickerScene__
#define __FenneXTestProject__TestImagePickerScene__

#include "FenneXCore.h"

class TestImagePickerScene : public FenneX::Scene
{
public:
    TestImagePickerScene(SceneName identifier, CCDictionary* parameters);
    void pickImage(Ref* obj);
    void onImagePicked(Ref* obj);
    void stop();
protected:
    //Keep track of local files to remove them when quitting the scene
    std::vector<std::string> localFiles;
};

#endif /* defined(__FenneXTestProject__TestImagePickerScene__) */
