#ifndef GRAPHICS_MESH_H_
#define GRAPHICS_MESH_H_

#include <stdlib.h>

class Mesh {
//  создание вершинных буфферов и их подготовка
    unsigned int vao;
    unsigned int vbo;

    size_t vertices;  // вершины
public:
    Mesh(const float* buffer, size_t vertices, const int* attrs);  // класс mesh
    ~Mesh();  // удаление класса mesh

    void draw(unsigned int primitive);  // отрисовка mesh
};

#endif

