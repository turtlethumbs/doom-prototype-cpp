#include "Application.hpp"

Application::Application() : device(nullptr), player(nullptr), camera(nullptr) {}

Application::~Application()
{
    if (device) device->drop();
}

bool Application::initialize()
{
    bool isFullScreen, isVsyncEnabled = true;
    bool useStencilBuffer = false;

    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 800), 16, isFullScreen, useStencilBuffer, isVsyncEnabled, &receiver);
    if (!device) return false;

    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    setupScene();
    setupCollision();

    return true;
}

void Application::run()
{
    int lastFPS = -1;
    irr::u32 then = device->getTimer()->getTime();

    while (device->run())
    {
        const irr::u32 now = device->getTimer()->getTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
        then = now;

        if (receiver.IsKeyDown(irr::KEY_ESCAPE)) {
            device->closeDevice();
        }

        player->update(receiver, frameDeltaTime);
        camera->update(player->getNode());

        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();

        int fps = driver->getFPS();
        if (lastFPS != fps)
        {
            irr::core::stringw tmp(L"Prototype-Doom 0.0.1 [");
            tmp += driver->getName();
            tmp += L"] fps: ";
            tmp += fps;

            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
    }
}

void Application::setupScene()
{
    smgr->loadScene("../../assets/scenes/test_scene1.irr");

    player = new Player(smgr, driver);
    camera = new Camera(smgr, player->getNode());

    device->getCursorControl()->setVisible(false);
}

void Application::setupCollision()
{
    irr::scene::IMetaTriangleSelector* meta = smgr->createMetaTriangleSelector();
    irr::core::array<irr::scene::ISceneNode*> nodes;
    smgr->getSceneNodesFromType(irr::scene::ESNT_ANY, nodes);

    for (irr::u32 i = 0; i < nodes.size(); ++i)
    {
        irr::scene::ISceneNode* node = nodes[i];
        irr::scene::ITriangleSelector* selector = nullptr;

        switch (node->getType())
        {
        case irr::scene::ESNT_CUBE:
        case irr::scene::ESNT_ANIMATED_MESH:
            selector = smgr->createTriangleSelectorFromBoundingBox(node);
            break;
        case irr::scene::ESNT_MESH:
        case irr::scene::ESNT_SPHERE:
            selector = smgr->createTriangleSelector(((irr::scene::IMeshSceneNode*)node)->getMesh(), node);
            break;
        case irr::scene::ESNT_TERRAIN:
            selector = smgr->createTerrainTriangleSelector((irr::scene::ITerrainSceneNode*)node);
            break;
        case irr::scene::ESNT_OCTREE:
            selector = smgr->createOctreeTriangleSelector(((irr::scene::IMeshSceneNode*)node)->getMesh(), node);
            break;
        default:
            break;
        }

        if (selector)
        {
            meta->addTriangleSelector(selector);
            selector->drop();
        }
    }

    irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        meta,
        player->getNode(),
        irr::core::vector3df(0.75f, 1.82f, 0.75f),
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(0, -9.8f, 0)
    );
    meta->drop();

    player->addAnimator(anim);
    anim->drop();
}
