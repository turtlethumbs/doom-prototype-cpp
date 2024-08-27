#include "Camera.hpp"

Camera::Camera(ISceneManager* smgr, ISceneNode* playerNode) : smoothingFactor(0.1f)
{
    offset = core::vector3df(0, 1.75f, 0);
    cameraNode = smgr->addCameraSceneNode();
    cameraNode->setParent(playerNode);
    cameraNode->bindTargetAndRotation(false);
    cameraNode->setNearValue(0.1f);
}

void Camera::update(ISceneNode* playerNode, f32 deltaTime)
{
    // Update the camera to be exactly at the player's position with offset
    cameraNode->setPosition(offset);

    // Calculate the player's forward direction based on rotation
    core::matrix4 rotationMatrix;
    rotationMatrix.setRotationDegrees(playerNode->getRotation());
    core::vector3df forwardDir(0, 0, 1);
    rotationMatrix.transformVect(forwardDir);

    // Calculate the target position for the camera with smoothing
    core::vector3df targetPosition = playerNode->getPosition() + forwardDir * 2.0f + core::vector3df(0, 1.75f, 0);
    core::vector3df currentTarget = cameraNode->getTarget();

    // Apply smoothing factor to the target position
    currentTarget = currentTarget.getInterpolated(targetPosition, smoothingFactor * deltaTime);

    cameraNode->setTarget(currentTarget);

    // Smooth rotation
    core::vector3df currentRotation = cameraNode->getRotation();
    core::vector3df targetRotation = playerNode->getRotation();

    currentRotation = currentRotation.getInterpolated(targetRotation, smoothingFactor * deltaTime);
    cameraNode->setRotation(currentRotation);
}
