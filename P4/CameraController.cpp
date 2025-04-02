#include "CameraController.h"
#include "CameraManager.h"
#include "Input.h"
#include "Time.h"

CameraController::CameraController() : AGameObject("CameraController")
{
	
}

CameraController::~CameraController()
{

}

void CameraController::initialize()
{
	this->camera = CameraManager::getInstance()->getCamera();
	this->setPosition(this->camera->getPosition());
	std::cout << "Camera Controller initialized." << "\n";
}

void CameraController::update()
{
	glm::vec3 velocity(0.0f);
	if (Input::isKey(GLFW_KEY_W))
	{
		velocity.z = 1.0f;
	}
	else if (Input::isKey(GLFW_KEY_S))
	{
		velocity.z = -1.0f;
	}

	if (Input::isKey(GLFW_KEY_D))
	{
		velocity.x = 1.0f;
	}
	else if (Input::isKey(GLFW_KEY_A))
	{
		velocity.x = -1.0f;
	}
	
	if (velocity != glm::vec3(0.0f))
	{
		velocity = glm::normalize(velocity);
		velocity *= this->speed * Time::getDeltaTime();
		this->translate(velocity);

		glm::vec3 pos = this->getPosition();
		this->camera->setPosition(pos);
		std::cout << "Cam Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
	}
}

void CameraController::draw()
{

}
