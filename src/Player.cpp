#include "Player.hpp"

Player::Player(ISceneManager* smgr, IVideoDriver* driver)
{
    createCylinder(0.75f, 1.82f, 16);
    playerNode = smgr->addMeshSceneNode(CylinderMesh);
    CylinderMesh->drop(); // Drop the mesh as it's now managed by the scene node

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

void Player::createCylinder(f32 radius, f32 height, u32 segments)
{
    CylinderMesh = new scene::SMesh();
    scene::SMeshBuffer* buffer = new scene::SMeshBuffer();

    // Ensure segments is at least 3 for a valid cylinder
    if (segments < 3) segments = 3;

    u32 numVertices = segments * 2 + 2; // Top and bottom center vertices + side vertices
    u32 numIndices = segments * 12; // 12 indices per segment for top, bottom, and side faces

    buffer->Vertices.set_used(numVertices);
    buffer->Indices.set_used(numIndices);

    // Top and bottom center vertices
    buffer->Vertices[0] = video::S3DVertex(vector3df(0, height / 2, 0), vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), vector2df(0, 0));
    buffer->Vertices[1] = video::S3DVertex(vector3df(0, -height / 2, 0), vector3df(0, -1, 0), video::SColor(255, 255, 255, 255), vector2df(0, 1));

    f32 angleStep = core::PI * 2.0f / segments;
    for (u32 i = 0; i < segments; ++i) {
        f32 angle = i * angleStep;
        f32 x = radius * cos(angle);
        f32 z = radius * sin(angle);
        buffer->Vertices[i + 2] = video::S3DVertex(vector3df(x, height / 2, z), vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), vector2df(0, 0));
        buffer->Vertices[i + segments + 2] = video::S3DVertex(vector3df(x, -height / 2, z), vector3df(0, -1, 0), video::SColor(255, 255, 255, 255), vector2df(0, 1));
    }

    u32 index = 0;
    for (u32 i = 0; i < segments; ++i) {
        u32 next = (i + 1) % segments;
        // Top face
        buffer->Indices[index++] = 0;
        buffer->Indices[index++] = next + 2;
        buffer->Indices[index++] = i + 2;
        // Bottom face
        buffer->Indices[index++] = 1;
        buffer->Indices[index++] = i + segments + 2;
        buffer->Indices[index++] = next + segments + 2;
        // Side faces
        buffer->Indices[index++] = i + 2;
        buffer->Indices[index++] = next + 2;
        buffer->Indices[index++] = next + segments + 2;

        buffer->Indices[index++] = i + 2;
        buffer->Indices[index++] = next + segments + 2;
        buffer->Indices[index++] = i + segments + 2;
    }

    // Set material properties directly on the mesh buffer
    video::SMaterial material;
    material.Lighting = false;
    material.FogEnable = false;
    material.BackfaceCulling = false;
    buffer->Material = material;

    // Add the buffer to the mesh
    CylinderMesh->addMeshBuffer(buffer);
    buffer->drop(); // Drop the buffer since it's now managed by the mesh
}
