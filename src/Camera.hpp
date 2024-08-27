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
    void update(ISceneNode* playerNode, f32 deltaTime);

private:
    ICameraSceneNode* cameraNode;
    vector3df offset;
    f32 smoothingFactor;
};

#endif
