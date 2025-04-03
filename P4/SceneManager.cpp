#include "SceneManager.h"
#include "GameObjectManager.h"
#include "MeshDisplay.h"
#include "MeshManager.h"
SceneManager* SceneManager::sharedInstance = NULL;


SceneManager* SceneManager::getInstance()
{
    return sharedInstance;
}
void SceneManager::initialize(std::shared_ptr<SceneClient> client)
{
    sharedInstance = new SceneManager(client);
}
void SceneManager::destroy()
{
}
SceneManager::SceneManager(std::shared_ptr<SceneClient> client)
{
    this->client = client;
}

void SceneManager::createScene(String name, SceneObjects& sceneObjects)
{
    Scene* scene = new Scene(name);
    scene->registerSceneObjects(sceneObjects);
}

void SceneManager::cacheSceneTransforms(String name, SceneObjTransforms transforms)
{
    this->sceneTransforms.push_back(transforms);
   /* std::cout << "Scene : " << name << " Object: " << transforms.getName() << std::endl;
    std::cout << "Position: " << transforms.getPosX() << "," << transforms.getPosY() << "," << transforms.getPosZ() << "," << std::endl;
    std::cout << "Scale: " << transforms.getScaleX() << "," << transforms.getScaleY() << "," << transforms.getScaleZ() << "," << std::endl;*/
    
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

void SceneManager::loadMesh (String name)
{
    String data = client->StreamMesh(name);
    MeshDisplay* mesh = (MeshDisplay*)GameObjectManager::getInstance()->findObjectByName("MeshDisplay");
    MeshManager::getInstance()->loadMeshDataAsync(name, data, mesh, true);

}



SceneObjTransforms SceneManager::getObjTransforms(String meshID)
{
    for (int i = 0; i < this->sceneTransforms.size(); i++)
    {
        if (this->sceneTransforms[i].getName() == meshID)
        {
            return this->sceneTransforms[i];
        }
    }
}





