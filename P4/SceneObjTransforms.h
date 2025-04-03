#pragma once
#include "string"
class SceneObjTransforms
{
private:
	std::string sceneName;
	std::string name;
	float posX, posY, posZ;
	float scaleX, scaleY, scaleZ;
public:
	SceneObjTransforms();
	void setPos(float x, float y, float z);
	void setScale(float x, float y, float z);
	float getPosX();
	float getPosY();
	float getPosZ();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	std::string getName();
	void setName(std::string name);
	std::string getSceneName();
	void setSceneName(std::string name);
};

