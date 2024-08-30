#include "Player.hpp"
#include "CylinderCreator.hpp"
#include <iostream>

Player::Player(ISceneManager* sceneManager, IVideoDriver* driver): smgr(sceneManager)
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
    
    // Check for left mouse button press
    if (receiver.IsMouseButtonJustPressed(0)) // 0 is the index for the left mouse button
    {
        shootRaycast();
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

void Player::shootRaycast()
{
    if (!playerNode) return;

    // Get the player's current position and forward direction
    core::vector3df playerPosition = playerNode->getPosition();
    core::vector3df forwardDirection(0, 0, 1); // Forward direction (along Z axis)
    
    // Rotate the forwardDirection vector according to the player's current rotation
    core::matrix4 rotationMatrix;
    rotationMatrix.setRotationDegrees(playerNode->getRotation());
    rotationMatrix.transformVect(forwardDirection);
    
    // Normalize the forward direction
    forwardDirection.normalize();
    
    // Define a ray starting from the player's position and extending in the forward direction
    line3d<f32> ray(playerPosition, playerPosition + (forwardDirection * 10000.0f)); // Adjust length as needed

    // Perform raycasting using the scene collision manager
    ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
    ISceneNode* selectedSceneNode = collMan->getSceneNodeFromRayBB(ray);
    
    if (selectedSceneNode)
    {
        // Output the MeshNode ID to the debug log if an enemy is hit
        std::cout << "Ray hit a node! Node ID: " << selectedSceneNode->getID() << std::endl;
    }
    else
    {
        std::cout << "Ray did not hit any node." << std::endl;
    }
}
