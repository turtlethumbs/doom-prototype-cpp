#ifndef ENEMY_H
#define ENEMY_H

#include <irrlicht.h>
#include <ISceneNode.h>
#include "MyEventReceiver.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class Enemy : public ISceneNode
{
public:
    Enemy(ISceneManager* smgr, IVideoDriver* driver, s32 id);
    void addAnimator(scene::ISceneNodeAnimator* anim);
    ISceneNode* getNode() const;
    void update(f32 deltaTime);
    virtual void render() override;
    virtual const core::aabbox3d<f32>& getBoundingBox() const override;
    virtual u32 getMaterialCount() const override;
    virtual video::SMaterial& getMaterial(u32 i) override;

private:
    void createCylinder(f32 radius, f32 height, u32 segments);

    ISceneNode* enemyNode;
    scene::SMesh* CylinderMesh;
    core::aabbox3d<f32> boundingBox; // Bounding box for collision detection
    u32 materialCount;
    video::SMaterial material;
};

#endif // ENEMY_H
