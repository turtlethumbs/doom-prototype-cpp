#include "Player.hpp"
#include "CylinderCreator.hpp"

Player::Player(ISceneManager* smgr, IVideoDriver* driver)
{
    scene::IMesh* CylinderMesh = CylinderCreator::createCylinder(0.75f, 1.82f, 16, driver);
    playerNode = smgr->addMeshSceneNode(CylinderMesh);
    CylinderMesh->drop();

    if (playerNode)
    {
        playerNode->setPosition(core::vector3df(25, 0, 25));
        playerNode->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
        playerNode->setMaterialFlag(video::EMF_LIGHTING, false);
    }
}

void Player::addAnimator(scene::ISceneNodeAnimator* anim)
{
    playerNode->addAnimator(anim);
}

ISceneNode* Player::getNode() const
{
    return playerNode;
}

void Player::update(const MyEventReceiver& receiver, f32 deltaTime)
{
    core::vector3df forwardDir(0, 0, 1);
    core::vector3df rightDir(1, 0, 0);
    core::matrix4 rotationMatrix;
    rotationMatrix.setRotationDegrees(playerNode->getRotation());

    rotationMatrix.transformVect(forwardDir);
    rotationMatrix.transformVect(rightDir);
    forwardDir.normalize();
    rightDir.normalize(); // Ensure rightDir is normalized for consistent strafing

    int speedModifier = receiver.IsKeyDown(irr::KEY_SHIFT) ? 2 : 1;

    // Update player rotation
    if (receiver.IsKeyDown(irr::KEY_KEY_A))
        playerNode->setRotation(playerNode->getRotation() + core::vector3df(0, -rotationSpeed * deltaTime, 0));
    if (receiver.IsKeyDown(irr::KEY_KEY_D))
        playerNode->setRotation(playerNode->getRotation() + core::vector3df(0, rotationSpeed * deltaTime, 0));

    // Calculate movement directions
    core::vector3df movement(0, 0, 0);
    if (receiver.IsKeyDown(irr::KEY_KEY_W))
        movement += forwardDir * movementSpeed * speedModifier * deltaTime;
    if (receiver.IsKeyDown(irr::KEY_KEY_S))
        movement -= forwardDir * movementSpeed * speedModifier * deltaTime;
    if (receiver.IsKeyDown(irr::KEY_KEY_Q))
        movement -= rightDir * movementSpeed * speedModifier * deltaTime;  // Strafe left
    if (receiver.IsKeyDown(irr::KEY_KEY_E))
        movement += rightDir * movementSpeed * speedModifier * deltaTime;  // Strafe right

    core::vector3df newPosition = playerNode->getPosition() + movement;
    playerNode->setPosition(newPosition);
}
