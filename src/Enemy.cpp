#include "Enemy.hpp"
#include "CylinderCreator.hpp"

Enemy::Enemy(ISceneManager* smgr, IVideoDriver* driver, s32 id)
    : ISceneNode(nullptr, smgr, id), materialCount(1) // Initialize with default values
{
    scene::IMesh* cylinderMesh = CylinderCreator::createCylinder(0.75f, 1.82f, 16, driver);
    enemyNode = smgr->addMeshSceneNode(cylinderMesh, this);
    cylinderMesh->drop(); // Drop the mesh as it's now managed by the scene node

    if (enemyNode)
    {
        enemyNode->setPosition(core::vector3df(5, 0, 5));
        enemyNode->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
        enemyNode->setMaterialFlag(video::EMF_LIGHTING, false);

        // Set the bounding box based on the cylinder's size
        boundingBox = core::aabbox3d<f32>(-0.75f, -1.82f / 2, -0.75f, 0.75f, 1.82f / 2, 0.75f);
    }
}

void Enemy::update(f32 deltaTime) {
    // Implement update logic if needed
}

void Enemy::addAnimator(scene::ISceneNodeAnimator* anim) {
    enemyNode->addAnimator(anim);
}

ISceneNode* Enemy::getNode() const {
    return enemyNode;
}

void Enemy::render() {
    // Default render method implementation, required by ISceneNode
    if (enemyNode) {
        enemyNode->render();
    }
}

const core::aabbox3d<f32>& Enemy::getBoundingBox() const {
    return boundingBox;
}

u32 Enemy::getMaterialCount() const {
    return materialCount;
}

video::SMaterial& Enemy::getMaterial(u32 i) {
    if (i >= materialCount) {
        // Handle out-of-bounds access, return default material if necessary
        return material;
    }
    return material;
}
