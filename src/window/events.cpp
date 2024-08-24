#include "events.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <string.h>

bool* Events::_keys;
uint* Events::_frames;
uint Events::_current = 0;
float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;

#define _MOUSE_BUTTONS 1024


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (Events::_cursor_started) {
// обновление расстояния на которое сдвинулся курсор мыши
        Events::deltaX += xpos-Events::x;
        Events::deltaY += ypos-Events::y;
    }

    else {
        Events::_cursor_started = true;
    }
//  обновление позиции мыши
    Events::x = xpos;
    Events::y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode) { 
    if (action == GLFW_PRESS) {  // проверка на нажатие кнопок мыши
//      запись в массив
        Events::_keys[_MOUSE_BUTTONS+button] = true;
        Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
    }

    else if (action == GLFW_RELEASE) {  // проверка на отжатие кнопок мыши
//      удаление из массива
        Events::_keys[_MOUSE_BUTTONS+button] = false;
        Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {  // проверка на нажатие клавиш
//      запись в массив
        Events::_keys[key] = true;
        Events::_frames[key] = Events::_current;
    }
    
    else if (action == GLFW_RELEASE) { // проверка на отжатие клавиш
//      удаление из массива
        Events::_keys[key] = false;
        Events::_frames[key] = Events::_current;
    }
}

void window_size_callback(GLFWwindow* Window, int width, int height) {
    glViewport(0, 0, width, height);
    Window::width = width;
	Window::height = height;
}

int Events::initialize() {
    GLFWwindow* window = Window::window;

//  инициализация массивов
    _keys = new bool[1032];
    _frames = new uint[1032];

//  обнуляем их через memset()
    memset(_keys, false, 1032*sizeof(bool));
    memset(_frames, 0, 1032*sizeof(uint));

//  обновление массивов клавиш и курсора мыши
    glfwSetKeyCallback(window, key_callback);  // проверка и запись нажатий на клавиши(или отжатий клавиш) 
    glfwSetMouseButtonCallback(window, mouse_button_callback);  // проверка и запись нажатий на кнопoк мыши(или отжатий кнопок мыши)
    glfwSetCursorPosCallback(window, cursor_position_callback);  // обновление позиции курсора(и расстояния на которое сдвинулся курсор мыши)
    glfwSetWindowSizeCallback(window, window_size_callback);

    return 0;
}

bool Events::isPressed(int keycode) {
//  проверка на то не выходит ли код клавиши за пределы значения(на то что это не кнопка мыши)
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS) {
        return false;
    }
//  возвращаем клавишу
    return _keys[keycode];
}

bool Events::justPressed(int keycode) {
//  проверка на то не выходит ли код клавиши за пределы значения(на то что это не кнопка мыши)
    if (keycode < 0 || keycode >= _MOUSE_BUTTONS) {
        return false;
    }
//  возвращаем клавишу если она нажата только что
    return _keys[keycode] && _frames[keycode] == _current;
}

bool Events::isclicked(int button) {
    int index = _MOUSE_BUTTONS+button;
    return _keys[index];  // возвращаем кнопку мыши
}

bool Events::justclicked(int button) {
    int index = _MOUSE_BUTTONS+button;
    return _keys[index] && _frames[index] == _current;  // возвращаем кнопку мыши если она нажата только что
}

void Events::toogleCursor() {
    Events::_cursor_locked = !Events::_cursor_locked;
    Window::setCursorMode(_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);  // захват или отпуск курсора
}

void Events::pullEvents() {
    _current++;
//  обнуление расстояния на которое сдвинулся курсор мыши
    deltaX = 0.0f;
    deltaY = 0.0f;
    glfwPollEvents();  // получение событий
}