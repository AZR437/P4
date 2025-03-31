#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera
{
private:
	float fov;
	float near;
	float far;

public:
	PerspectiveCamera(
		glm::vec3 position,
		glm::vec3 center = glm::vec3(0.0f),
		float fov = 45.f,
		float near = 0.1f,
		float fat = 100.0f
	);

private:
	glm::mat4 calcProjection();

public:
	float getFOV();
	void setFOV(float fov);

	float getNear();
	void setNear(float near);

	float getFar();
	void setFar(float far);
};