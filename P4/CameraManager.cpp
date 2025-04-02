#include "CameraManager.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"

CameraManager* CameraManager::sharedInstance = NULL;

CameraManager* CameraManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new CameraManager();

	return sharedInstance;
}

Camera* CameraManager::getCamera()
{
	return this->camera;
}

CameraManager::CameraManager()
{
	this->camera = new PerspectiveCamera(glm::vec3(0.0f, 0.0f, 0.0f));
}

CameraManager::~CameraManager()
{
	delete this->camera;
}
