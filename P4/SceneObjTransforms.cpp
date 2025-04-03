#include "SceneObjTransforms.h"

SceneObjTransforms::SceneObjTransforms()
{
	
}

void SceneObjTransforms::setPos(float x, float y, float z)
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}

void SceneObjTransforms::setScale(float x, float y, float z)
{
	this->scaleX = x;
	this->scaleY = y;
	this->scaleZ = z;
}

float SceneObjTransforms::getPosX()
{
	return this->posX;
}
float SceneObjTransforms::getPosY()
{
	return this->posY;
}
float SceneObjTransforms::getPosZ()
{
	return this->posZ;
}
float SceneObjTransforms::getScaleX()
{
	return this->scaleX;
}
float SceneObjTransforms::getScaleY()
{
	return this->scaleY;
}
float SceneObjTransforms::getScaleZ()
{
	return this->scaleZ;
}

std::string SceneObjTransforms::getName()
{
	return this->name;
}

void SceneObjTransforms::setName(std::string name)
{
	this->name = name;
}

std::string SceneObjTransforms::getSceneName()
{
	return this->sceneName;
}

void SceneObjTransforms::setSceneName(std::string name)
{
	this->sceneName = sceneName;
}
