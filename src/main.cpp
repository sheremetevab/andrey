#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

#include "window/window.h"
#include "window/window.cpp"
#include "window/events.h"
#include "window/events.cpp"
#include "graphics/shader.h"
#include "graphics/shader.cpp"
#include "loaders/png_loading.h"
#include "loaders/png_loading.cpp"
#include "graphics/texture.h"
#include "graphics/texture.cpp"
#include "window/camera.h"
#include "window/camera.cpp"
#include "graphics/mesh.h"
#include "graphics/mesh.cpp"
#include "voxels/voxel.h"
#include "voxels/voxel.cpp"
#include "voxels/chunk.h"
#include "voxels/chunk.cpp"
#include "graphics/VoxelsRenderer.h"
#include "graphics/VoxelsRenderer.cpp"

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
		// x    y     z     u     v
	   -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int attrs[] = {
		3,2,  0 //null terminator
};

float PLAYER_SPEED = 8;

int main() {
    Window::initialize(WIDTH, HEIGHT, "hello world");  // инициализация окна(подготовка окна)
    Events::initialize();  // инициализация функций Events

    Shader* shader = load_shader("/home/kamerad/Documents/test3/res/main.glslv", "/home/kamerad/Documents/test3/res/main.glslf");  // создание шейдров

//  проверка на ошибки
    if (shader == nullptr) {  
        std::cerr << "failed to load shader" << std::endl;
        Window::terminate();
        return 1;
    }

    Texture* texture = load_texture("/home/kamerad/Documents/test3/res/block1.png");  // загрузка текстуры

//  проверка на ошибки   
    if (texture == nullptr) {
        std::cerr << "failed to load texture" << std::endl;
        delete shader;
        Window::terminate();
        return 1;
    }

	VoxelRenderer renderer(1024*1024*8);
	Chunk* chunk = new Chunk();  // создание чанка
	Mesh* mesh = renderer.render(chunk);  // создание mesh
	glClearColor(0.6f,0.62f,0.65f,1);

//  смешивание
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Camera* camera = new Camera(vec3(0,0,20), radians(90.0f));  // создание камеры

	mat4 model(1.0f);  // создание матрицы объекта
	model = translate(model, vec3(0.5f,0,0));

	float lastTime = glfwGetTime();  // время прошедшего кадра
    float delta = 0.0f;
    
//  повернутость камеры
    float camX = 0.0f;
    float camY = 0.0f;

	float speed = 5;

	while (!Window::isShouldClose()) {  // проверка на закрытие окна
        float currentTime = glfwGetTime();  // время текущего кадра
        delta = currentTime - lastTime;
        lastTime = currentTime;  // обновление времени прошедшего кадра

//      закрытие окна если нажат escape
        if (Events::justPressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(true);
        }

//      смена цвета окна
        if (Events::justclicked(GLFW_MOUSE_BUTTON_1)){
			glClearColor(0.8f,0.4f,0.2f,1);
		}
        if (Events::justclicked(GLFW_MOUSE_BUTTON_2)){
			glClearColor(0.6f,0.62f,0.65f,1);
		}

//      настройка захвата курсора
        if (Events::justPressed(GLFW_KEY_TAB)) {
            Events::toogleCursor();
        }

		PLAYER_SPEED = 5 * delta;  // обновление скорости

//      передвижение
        if (Events::isPressed(GLFW_KEY_Q)) {
            if (Events::isPressed(GLFW_KEY_S)) {
                camera->position -= camera->front * PLAYER_SPEED;
            }
            if (Events::isPressed(GLFW_KEY_W)) {
                camera->position += camera->front * (PLAYER_SPEED * 2);
            }
            if (Events::isPressed(GLFW_KEY_D)) {
                camera->position += camera->right * (PLAYER_SPEED * 2);
            }
            if (Events::isPressed(GLFW_KEY_A)) {
                camera->position -= camera->right * (PLAYER_SPEED * 2);
            }
            if (Events::isPressed(GLFW_KEY_SPACE)) {
                camera->position += camera->up * (PLAYER_SPEED * 2);
            }
            if (Events::isPressed(GLFW_KEY_LEFT_SHIFT)) {
                camera->position -= camera->up * (PLAYER_SPEED * 2);
            }
        } else {
            if (Events::isPressed(GLFW_KEY_S)) {
                camera->position -= camera->front * PLAYER_SPEED;
            }
            if (Events::isPressed(GLFW_KEY_W)) {
                camera->position += camera->front * PLAYER_SPEED;
            }
            if (Events::isPressed(GLFW_KEY_D)) {
                camera->position += camera->right * PLAYER_SPEED;
            }
            if (Events::isPressed(GLFW_KEY_A)) {
                camera->position -= camera->right * PLAYER_SPEED;
            }
            if (Events::isPressed(GLFW_KEY_SPACE)) {
                camera->position += camera->up * PLAYER_SPEED;
            }
            if (Events::isPressed(GLFW_KEY_LEFT_SHIFT)) {
                camera->position -= camera->up * PLAYER_SPEED;
            }
        }

		if (Events::_cursor_locked) {
            camX += -Events::deltaX / Window::height * 2;
            camY += -Events::deltaY / Window::width * 2;

//          ограничение на поворот вверх или вниз
            if (camY < -radians(89.0f)) {
                camY = -radians(89.0f);
            }
            if (camY > radians(89.0f)) {
                camY = radians(89.0f);
            }
            camera->rotation = mat4(1.0f);  // обнуление матрицы поворота
            camera->rotate(camY, camX, 0);  // поворот камеры по движению курсора

        }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();  // используем шейдры
        shader->uniformMatrix("model", model);  // передача матрицы шейдру
        shader->uniformMatrix("projview", camera->getProjection()*camera->getView());  // передача матриц проекции и вида шейдру
        texture->bind();  // привязка текстуры
        mesh->draw(GL_TRIANGLES);  // отрисовка
        Window::swapBuffers();  // смена буфферов
        Events::pullEvents();  // получение событий в игре
	}
//  освобождение всех ресурсов
	delete shader;
	delete texture;
	delete mesh;
	delete chunk;

	Window::terminate();
	return 0;
}

