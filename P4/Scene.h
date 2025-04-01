#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "AGameObject.h"
class Scene
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> SceneObjects;

	Scene(String name);
	~Scene();
	
	void registerSceneObject(AGameObject* gameObject);
	void registerSceneObjects(SceneObjects& gameObjects);
	void unregisterSceneObject(AGameObject* gameObject);
	void setSceneObjectsEnabled(bool enabled);
	SceneObjects& getSceneObjects();

private:
	String name;
	SceneObjects sceneObjects;
};

