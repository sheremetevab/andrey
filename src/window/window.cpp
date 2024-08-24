#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "window.h"

GLFWwindow* Window::window;
int Window::width = 0;
int Window::height = 0;

int Window::initialize(int width, int height, const char* title) {

//  подготовка к созданию окна и инициализация glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

//  создание окна и проверка на ошибки
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "error to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // создание контекста

//  инициализация glew и проверка на ошибки
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "error glew init" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, width, height);
    
    Window::width = width;
	Window::height = height;
    return 0;
};

void Window::setCursorMode(int mode) {
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}

bool Window::isShouldClose() {
    return glfwWindowShouldClose(window);  // проверка на закрытие окна
};

void Window::swapBuffers() {
    glfwSwapBuffers(window);  // смена буфферов
};

void Window::terminate() {
    glfwTerminate();  // освобождение ресурсов
}

void Window::setShouldClose(bool flag) {
    glfwSetWindowShouldClose(window, flag);
}