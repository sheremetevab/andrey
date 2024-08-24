#include "shader.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <execution>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(unsigned int id) : id(id) {

}

Shader::~Shader() {
    glDeleteProgram(id);  // удаляем шейдерную программу 
}

void Shader::use() {
    glUseProgram(id);  // используем шейдерную программу 
}

void Shader::uniformMatrix(std::string name, glm::mat4 matrix){
	GLuint transformLoc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}


Shader* load_shader(std::string vertexFile, std::string fragmentFile) {

//  код по загрузке текстов из файлов
//  создание переменных
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {
//      открытие файлов и их чтение
        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
//      закрытие файлов
        vShaderFile.close();
        fShaderFile.close();
//      запись кода шейдров в переменные
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
//  проверка на ошибки
    catch(std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return nullptr;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();


    GLuint vertex, fragment;  // переменные с id созданных шейдров
    GLint success;  // статус компиляции
    GLchar infolog[512];  // лог для шейдров(в случае ошибки)

// vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);  // создание вершинного шейдра
    glShaderSource(vertex, 1, &vShaderCode, nullptr);  // загрузка текста в шейдер
    glCompileShader(vertex);  // компиляция шейдра 
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);  // получение и запись статуса компиляции

//  проверка на ошибки
    if (!success) {  
        glGetShaderInfoLog(vertex, 512, nullptr, infolog);  // получение и запись ошибки
        std::cerr << "error: vertex shader compilation failed" << std::endl;
        std::cerr << "log:" << infolog << std::endl;
        return nullptr;
    }


// fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);  // создание вершинного шейдра
    glShaderSource(fragment, 1, &fShaderCode, nullptr);  // загрузка текста в шейдер
    glCompileShader(fragment);  // компиляция шейдра 
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);  // получение и запись статуса компиляции

//  проверка на ошибки
    if (!success) {  
        glGetShaderInfoLog(fragment, 512, nullptr, infolog);  // получение и запись ошибки
        std::cerr << "error: fragment shader compilation failed" << std::endl;
        std::cerr << "log:" << infolog << std::endl;
        return nullptr;
    }


// shader program
    GLuint id = glCreateProgram();  // создание шейдерной программы

//  линкуем шейдры
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);  // получаем статус линковки
//      удаление шейдров и программы
//  проверка на ошибки
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infolog);  // получение и запись ошибки
        std::cerr << "error: shader program linked failed" << std::endl;
        std::cerr << "log:" << infolog << std::endl;

//      удаление шейдров и программы
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(id);
        return nullptr;
    }


//  удаление шейдров 
    glDeleteShader(vertex);
    glDeleteShader(fragment);

//  возвращаем шейдерную программу
    return new Shader(id);
}


