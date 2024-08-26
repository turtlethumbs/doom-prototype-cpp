#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <irrlicht.h>
#include "MyEventReceiver.hpp"
#include "Player.hpp"
#include "Camera.hpp"

using namespace irr;

class Application
{
public:
    Application();
    ~Application();
    bool initialize();
    void run();

private:
    IrrlichtDevice* device;
    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;
    gui::IGUIEnvironment* guienv;

    MyEventReceiver receiver;
    Player* player;
    Camera* camera;

    void setupScene();
    void setupCollision();
};

#endif // APPLICATION_HPP
