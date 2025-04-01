#include "SceneManager.h"
#include "GameObjectManager.h"

SceneManager* SceneManager::sharedInstance = NULL;

SceneManager* SceneManager::getInstance()
{
    if (sharedInstance == NULL)
        sharedInstance = new SceneManager();

    return sharedInstance;
}

void SceneManager::createScene(String name, SceneObjects& sceneObjects)
{
    Scene* scene = new Scene(name);
    scene->registerSceneObjects(sceneObjects);
}

void SceneManager::destroyScene(String name, bool destroyObjects)
{
    if (destroyObjects)
    {
        for (auto gameObject : this->sceneMap[name]->getSceneObjects())
        {
            GameObjectManager::getInstance()->deleteObject(gameObject);
        }
    }

    delete this->sceneMap[name];
    this->sceneMap.erase(name);
}

Scene* SceneManager::getScene(String name)
{
    return this->sceneMap[name];
}
