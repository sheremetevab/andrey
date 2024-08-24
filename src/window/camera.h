#ifndef WINDOW_CAMERA_H_
#define WINDOW_CAMERA_H_

#include <glm/glm.hpp>
using namespace glm;

class Camera {
    void updateVectors();  // обновление векторов
public:
//  векторы направления
    vec3 front;
	vec3 up;
	vec3 right;

	vec3 position;  // позиция камеры
	float fov;  // поле зрения камеры
	mat4 rotation;  // матрица вращения
	Camera(vec3 position, float fov);

	void rotate(float x, float y, float z);  // обновление матрици rotation

	mat4 getProjection();  // получение матрици проекции 
	mat4 getView();  // получение матрици вида
};

#endif