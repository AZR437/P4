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

void SceneManager::cacheSceneTransforms(String name, String meshID, SceneObjTransforms transforms)
{
    this->sceneTransforms[name][meshID] = transforms;
    std::cout << "Scene : " << name << " Object: " << meshID << std::endl;
    std::cout << "Position: " << transforms.getPosX() << "," << transforms.getPosY() << "," << transforms.getPosZ() << "," << std::endl;
    std::cout << "Scale: " << transforms.getScaleX() << "," << transforms.getScaleY() << "," << transforms.getScaleZ() << "," << std::endl;
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

SceneObjTransforms SceneManager::getObjTransforms(String name, String meshID)
{
    return this->sceneTransforms[name][meshID];
}




