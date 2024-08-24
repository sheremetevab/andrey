#ifndef GRAPHICS_VOXELRENDERER_H_
#define GRAPHICS_VOXELRENDERER_H_

#include <stdlib.h>

class Mesh;
class Chunk;

class VoxelRenderer {
    float* buffer;  // вместимость
    size_t capacity;
public:
    VoxelRenderer(size_t capacity);  // создание рендера
    ~VoxelRenderer();  // удаление рендера

    Mesh* render(Chunk* chunk);  // отрисовка 
};

#endif

