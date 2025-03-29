#include "AGameObject.h"

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

void AGameObject::draw(GLFWwindow* targetWindow) {
	/*if (this->sprite != nullptr) {
		this->sprite->setPosition(this->posX, this->posY);
		this->sprite->setScale(this->scaleX, this->scaleY);
		targetWindow->draw(*this->sprite);
	}*/
}

//must be called after being registered to the game object manager or one of the parent game objects
void AGameObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	//if(this->sprite != nullptr)
	//{
	//	this->sprite->setPosition(this->posX, this->posY);
	//}
}

void AGameObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	//if (this->sprite != nullptr)
	//{
	//	this->sprite->setScale(this->scaleX, this->scaleY);
	//}
}

void AGameObject::setPriority(int priority)
{
	this->priority = priority;
}

//sf::Vector2f AGameObject::getPosition()
//{
//	return this->sprite->getPosition();
//}
//
//sf::Vector2f AGameObject::getScale()
//{
//	return this->sprite->getScale();
//}

int AGameObject::getPriority()
{
	return this->priority;
}
