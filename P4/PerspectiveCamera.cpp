#include "PerspectiveCamera.h"
#include "BaseRunner.h"

PerspectiveCamera::PerspectiveCamera(
	glm::vec3 position,
	glm::vec3 center,
	float fov,
	float near,
	float far)
	: Camera(position, center) {
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->projection = this->calcProjection();
}

glm::mat4 PerspectiveCamera::calcProjection() {
	float aspect = static_cast<float>(BaseRunner::WINDOW_WIDTH) / BaseRunner::WINDOW_HEIGHT;
	return glm::perspective(
		glm::radians(this->fov),
		aspect,
		this->near,
		this->far
	);
}

float PerspectiveCamera::getFOV() {
	return this->fov;
}

void PerspectiveCamera::setFOV(float fov) {
	this->fov = fov;
	this->projection = this->calcProjection();
}

float PerspectiveCamera::getNear() {
	return this->near;
}

void PerspectiveCamera::setNear(float near) {
	this->near = near;
	this->projection = this->calcProjection();
}

float PerspectiveCamera::getFar() {
	return this->far;
}

void PerspectiveCamera::setFar(float far) {
	this->far = far;
	this->projection = this->calcProjection();
}