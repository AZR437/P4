#include "LightManager.h"

LightManager* LightManager::sharedInstance = NULL;

LightManager* LightManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new LightManager();

	return sharedInstance;
}

void LightManager::addLight(Light* light)
{
	this->lights.push_back(light);
}

void LightManager::deleteLight(Light * light)
{
	int index = -1;
	for (int i = 0; i < this->lights.size() && index == -1; i++)
	{
		if (this->lights[i] == light) index = i;
	}

	if (index != -1) this->lights.erase(this->lights.begin() + index);
	delete light;
}

LightManager::Lights& LightManager::getLights()
{
	return this->lights;
}
