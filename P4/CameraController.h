#pragma once
#include "AGameObject.h"
#include "Camera.h"
class CameraController : public AGameObject
{
public:
	CameraController();
	~CameraController();

	void initialize() override;
	void update() override;
	void draw() override;

private:
	void rotate();
	void move();

private:
	Camera* camera;
	float moveSpeed = 50.0f;
	float rotSpeed = 0.5f;
	glm::vec2 lastMousePos = glm::vec2(0.0f);
};

