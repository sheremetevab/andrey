#include "mesh.h"
#include <GL/glew.h>

Mesh::Mesh(const float* buffer, size_t vertices, const int* attrs) : vertices(vertices) {
    int vertex_size = 0;

//  установка размера вершин
    for (int i = 0; attrs[i]; i++) {
        vertex_size += attrs[i];
    }

//  создание массивов vao, vbo
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

//  привязка массивов vao, vbo
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);  // создание хранилища данных для vbo

    int offset = 0;
    for (int i = 0; attrs[i]; i++) {
        int size = attrs[i];
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));  // определение массива общих данных атрибутов вершин
        glEnableVertexAttribArray(i);  // включение универсального массива атрибутов вершин
        offset += size;
    }

    glBindVertexArray(0);  // привязка объекта массива вершин
}

Mesh::~Mesh() {
//  удаление массивов vbo, vao
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh::draw(unsigned int primitive) {
    glBindVertexArray(vao);
    glDrawArrays(primitive, 0, vertices);  // отрисовка
    glBindVertexArray(0);
}
