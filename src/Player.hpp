#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include "MyEventReceiver.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class Player
{
public:
    Player(ISceneManager* smgr, IVideoDriver* driver);
    void addAnimator(scene::ISceneNodeAnimator* anim);
    ISceneNode* getNode() const;
    void update(const MyEventReceiver& receiver, f32 deltaTime);

private:
    void createCylinder(f32 radius, f32 height, u32 segments);
    void moveForward(f32 deltaTime);
    void moveBackward(f32 deltaTime);
    void shootRaycast();
    void strafeLeft(f32 deltaTime);
    void strafeRight(f32 deltaTime);

    ISceneNode* playerNode;
    scene::SMesh* CylinderMesh;
    ISceneManager* smgr;
    f32 movementSpeed = 10.0f; // Adjust as needed
    f32 strafeSpeed = 10.0f;   // Adjust as needed
    f32 rotationSpeed = 60.0f; // Degrees per second
};

#endif // PLAYER_H
