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
	this->rotate();
	this->move();
}

void CameraController::draw()
{

}

void CameraController::rotate()
{
	glm::vec2 mousePos = Input::getCursorPosition();
	if (Input::isMouseButton(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (mousePos != this->lastMousePos)
		{
			//glm::vec2 lastMousePos = this->lastMousePos;
			glm::vec2 deltaMousePos = mousePos - this->lastMousePos;
			this->lastMousePos = mousePos;

			float swivelTheta = deltaMousePos.x * this->rotSpeed * Time::getDeltaTime();
			float tiltTheta = deltaMousePos.y * this->rotSpeed * Time::getDeltaTime();

			this->camera->swivel(swivelTheta, glm::vec3(0.0f, 1.0f, 0.0f));
			this->camera->tilt(tiltTheta, glm::vec3(1.0f, 0.0f, 0.0f));

			//Input::setCursorPosition(lastMousePos);
		}
	}
	else this->lastMousePos = mousePos;
}

void CameraController::move()
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
	
	if (Input::isKey(GLFW_KEY_E))
	{
		velocity.y = 1.0f;
	}
	else if (Input::isKey(GLFW_KEY_Q))
	{
		velocity.y = -1.0f;
	}

	if (velocity != glm::vec3(0.0f))
	{
		velocity = glm::normalize(velocity);
		velocity *= this->moveSpeed * Time::getDeltaTime();
		this->camera->move(velocity.z, velocity.x, velocity.y);

		glm::vec3 pos = this->camera->getPosition();
		std::cout << "Cam Position: (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
	}
}
