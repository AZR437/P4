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
	Camera* camera;
	float speed = 100.0f;
};

