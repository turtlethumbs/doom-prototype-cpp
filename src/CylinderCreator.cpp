// CylinderCreator.cpp
#include "CylinderCreator.hpp"

scene::IMesh* CylinderCreator::createCylinder(f32 radius, f32 height, u32 segments, video::IVideoDriver* driver)
{
    scene::SMesh* CylinderMesh = new scene::SMesh();
    scene::SMeshBuffer* buffer = new scene::SMeshBuffer();

    if (segments < 3) segments = 3;

    u32 numVertices = segments * 2 + 2;
    u32 numIndices = segments * 12;

    buffer->Vertices.set_used(numVertices);
    buffer->Indices.set_used(numIndices);

    buffer->Vertices[0] = video::S3DVertex(core::vector3df(0, height / 2, 0), core::vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), core::vector2df(0, 0));
    buffer->Vertices[1] = video::S3DVertex(core::vector3df(0, -height / 2, 0), core::vector3df(0, -1, 0), video::SColor(255, 255, 255, 255), core::vector2df(0, 1));

    f32 angleStep = core::PI * 2.0f / segments;
    for (u32 i = 0; i < segments; ++i) {
        f32 angle = i * angleStep;
        f32 x = radius * cos(angle);
        f32 z = radius * sin(angle);
        buffer->Vertices[i + 2] = video::S3DVertex(core::vector3df(x, height / 2, z), core::vector3df(0, 1, 0), video::SColor(255, 255, 255, 255), core::vector2df(0, 0));
        buffer->Vertices[i + segments + 2] = video::S3DVertex(core::vector3df(x, -height / 2, z), core::vector3df(0, -1, 0), video::SColor(255, 255, 255, 255), core::vector2df(0, 1));
    }

    u32 index = 0;
    for (u32 i = 0; i < segments; ++i) {
        u32 next = (i + 1) % segments;
        buffer->Indices[index++] = 0;
        buffer->Indices[index++] = next + 2;
        buffer->Indices[index++] = i + 2;

        buffer->Indices[index++] = 1;
        buffer->Indices[index++] = i + segments + 2;
        buffer->Indices[index++] = next + segments + 2;

        buffer->Indices[index++] = i + 2;
        buffer->Indices[index++] = next + 2;
        buffer->Indices[index++] = next + segments + 2;

        buffer->Indices[index++] = i + 2;
        buffer->Indices[index++] = next + segments + 2;
        buffer->Indices[index++] = i + segments + 2;
    }

    video::SMaterial material;
    material.Lighting = false;
    material.FogEnable = false;
    material.BackfaceCulling = false;
    buffer->Material = material;

    CylinderMesh->addMeshBuffer(buffer);
    buffer->drop();

    return CylinderMesh;
}
