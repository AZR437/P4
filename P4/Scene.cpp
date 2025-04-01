#include "Scene.h"

Scene::Scene(String name)
{
    this->name = name;
}

Scene::~Scene()
{

}

void Scene::registerSceneObject(AGameObject* gameObject)
{
    this->sceneObjects.push_back(gameObject);
}

void Scene::registerSceneObjects(SceneObjects& gameObjects)
{
    this->sceneObjects.insert(this->sceneObjects.end(), gameObjects.begin(), gameObjects.end());
}

void Scene::unregisterSceneObject(AGameObject* gameObject)
{
	int index = -1;
	for (int i = 0; i < this->sceneObjects.size() && index == -1; i++)
	{
		if (this->sceneObjects[i] == gameObject) index = i;
	}

	if (index != -1) this->sceneObjects.erase(this->sceneObjects.begin() + index);

}

void Scene::setSceneObjectsEnabled(bool enabled)
{
    for (auto sceneObject : this->sceneObjects)
    {
        sceneObject->setEnabled(enabled);
    }
}

Scene::SceneObjects& Scene::getSceneObjects()
{
    return this->sceneObjects;
}
