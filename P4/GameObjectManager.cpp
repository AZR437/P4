#include "GameObjectManager.h"
#include <algorithm>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	if (sharedInstance == NULL) {
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(AGameObject::String name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

List GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::processInput() {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i]->getEnabled())
		{
			//this->gameObjectList[i]->processInput(event);
		}
	}
}

void GameObjectManager::update()
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i]->getEnabled())
			this->gameObjectList[i]->update();
	}
}

//draws the object if it contains a sprite
void GameObjectManager::draw(GLFWwindow* window) {
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i]->getEnabled())
			this->gameObjectList[i]->draw();
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	//also initialize the oject
	this->gameObjectMap[gameObject->getName()] = gameObject;
	this->gameObjectList.push_back(gameObject);
	this->gameObjectMap[gameObject->getName()]->initialize();
}

//also frees up allocation of the object.
void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}
	
	delete gameObject;
}

void GameObjectManager::deleteObjectByName(AGameObject::String name) {
	AGameObject* object = this->findObjectByName(name);
	
	if (object != NULL) {
		this->deleteObject(object);
	}
}

void GameObjectManager::sortObjects()
{
	auto first = this->gameObjectList.begin();
	auto last = this->gameObjectList.end();

	auto compare = [](AGameObject* a, AGameObject* b)
		{
			return a->getPriority() < b->getPriority();
		};

	std::sort(first, last, compare);
}
