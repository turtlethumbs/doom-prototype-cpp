// CylinderCreator.hpp
#ifndef CYLINDER_CREATOR_HPP
#define CYLINDER_CREATOR_HPP

#include <irrlicht.h>

using namespace irr;

class CylinderCreator
{
public:
    static scene::IMesh* createCylinder(f32 radius, f32 height, u32 segments, video::IVideoDriver* driver);
};

#endif
