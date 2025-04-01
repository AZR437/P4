#pragma once
#include <unordered_map>
#include "Scene.h"

class SceneManager
{
public:
    typedef std::string String;
    typedef std::vector<AGameObject*> SceneObjects;
    typedef std::unordered_map<String, Scene*> SceneMap;

    static SceneManager* getInstance();
    
    void createScene(String name, SceneObjects& sceneObjects);
    void destroyScene(String name, bool destroyObjects = false);
    Scene* getScene(String name);

private:
    SceneManager() {}
    SceneManager(const SceneManager&) {}
    SceneManager& operator = (const SceneManager&) {}
    static SceneManager* sharedInstance;

    SceneMap sceneMap;
};

