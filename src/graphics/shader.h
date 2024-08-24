#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include <string>
#include <glm/glm.hpp>


class Shader {
public:

    unsigned int id;  // id шейдерной программы
    Shader(unsigned int id);  // шейдерная программа
    ~Shader();  // удаление шейдерной программы

    void use();  // метод для использования шейдерной программы
    void uniformMatrix(std::string name, glm::mat4 matrix);  // создание функции для пересылки матрицы шейдру
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);  // метод для создания шейдерной программы


#endif