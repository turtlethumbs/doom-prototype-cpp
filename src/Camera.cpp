#include "Camera.hpp"

Camera::Camera(ISceneManager* smgr, ISceneNode* playerNode) : smoothingFactor(0.1f)
{
    offset = core::vector3df(0, 1.75f, -0.1f);
    cameraNode = smgr->addCameraSceneNode();
    cameraNode->setParent(playerNode);
    cameraNode->bindTargetAndRotation(true);
    cameraNode->setInputReceiverEnabled(false);
    cameraNode->setNearValue(0.1f);
}

void Camera::addAnimator(scene::ISceneNodeAnimator* anim)
{
    cameraNode->addAnimator(anim);
}

void Camera::update(ISceneNode* playerNode, f32 deltaTime)
{
    // Update the camera to be exactly at the player's position
    cameraNode->setTarget((playerNode->getPosition() + core::vector3df(0,1.75f,0.1f)));
    cameraNode->setPosition(offset);
    cameraNode->setRotation(playerNode->getRotation());
}
