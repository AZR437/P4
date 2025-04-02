#include "AGameObject.h"
#include <glm/gtc/matrix_transform.hpp>

AGameObject::AGameObject(String name)
{
	this->name = name;
}

AGameObject::~AGameObject() {
	
}

AGameObject::String AGameObject::getName() {
	return this->name;
}

bool AGameObject::getEnabled() const
{
	return this->enabled;
}

void AGameObject::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void AGameObject::translate(glm::vec3 translation)
{
    this->transformation = glm::translate(
        this->transformation,
        translation
    );
}

void AGameObject::translate(float x, float y, float z)
{
    this->translate(glm::vec3(x, y, z));
}

void AGameObject::scale(glm::vec3 escalation)
{
    this->transformation = glm::scale(
        this->transformation,
        escalation
    );
}

void AGameObject::scale(float x, float y, float z)
{
    this->scale(glm::vec3(x, y, z));
}

void AGameObject::scale(float scalar)
{
    this->scale(glm::vec3(scalar, scalar, scalar));
}

void AGameObject::rotate(float theta, glm::vec3 axis)
{
    this->transformation = glm::rotate(
        this->transformation,
        glm::radians(theta),
        glm::normalize(axis)
    );
}

void AGameObject::rotate(float theta, float x, float y, float z)
{
    this->rotate(theta, glm::vec3(x, y, z));
}

void AGameObject::setPosition(glm::vec3 position)
{
    this->transformation = glm::translate(glm::mat4(this->transformation[1][1]), position);
}

glm::mat4 AGameObject::getTransformation()
{
    return this->transformation;
}

glm::vec3 AGameObject::getPosition()
{
    return glm::vec3(this->transformation[3][0], this->transformation[3][1], this->transformation[3][2]);
}

void AGameObject::setPriority(int priority)
{
	this->priority = priority;
}

int AGameObject::getPriority()
{
	return this->priority;
}
