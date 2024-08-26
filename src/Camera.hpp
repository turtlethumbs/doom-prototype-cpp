#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace core;

class Camera
{
public:
    Camera(ISceneManager* smgr, ISceneNode* playerNode);
    void addAnimator(scene::ISceneNodeAnimator* anim);
    void update(ISceneNode* playerNode);

private:
    ICameraSceneNode* cameraNode;
    vector3df offset;
};

#endif
