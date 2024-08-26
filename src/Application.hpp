#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <irrlicht.h>
#include "MyEventReceiver.hpp"
#include "Player.hpp"
#include "Camera.hpp"

class Application
{
public:
    Application();
    ~Application();
    bool initialize();
    void run();

private:
    irr::IrrlichtDevice* device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* smgr;
    irr::gui::IGUIEnvironment* guienv;

    MyEventReceiver receiver;
    Player* player;
    Camera* camera;

    void setupScene();
    void setupCollision();
};

#endif // APPLICATION_HPP
