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
    ISceneNode* playerNode;
    const f32 movementSpeed = 20.f;
    const f32 rotationSpeed = 45.f;
    scene::SMesh* CylinderMesh;
    
    void createCylinder(f32 radius, f32 height, u32 segments);
};

#endif // PLAYER_H
