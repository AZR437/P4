#pragma once
#include <unordered_map>
#include "Scene.h"
#include "SceneObjTransforms.h"
#include "SceneClient.h"
class SceneManager
{
public:
    typedef std::string String;
    typedef std::vector<AGameObject*> SceneObjects;
    typedef std::unordered_map<String, Scene*> SceneMap;
    typedef std::vector<SceneObjTransforms> SceneTransforms;

    static SceneManager* getInstance();
    static void initialize(std::shared_ptr<SceneClient> client);
    static void destroy();
    void createScene(String name, SceneObjects& sceneObjects);
    void cacheSceneTransforms(String name, SceneObjTransforms transforms);
    void destroyScene(String name, bool destroyObjects = false);
    Scene* getScene(String name);
    void loadMesh(String name, String data);
    bool hasScene(String name);
    //for Testing
    SceneObjTransforms getObjTransforms(String meshID);

private:
    SceneManager(std::shared_ptr<SceneClient> client);
    SceneManager(const SceneManager&) {}
    SceneManager& operator = (const SceneManager&) {}
    static SceneManager* sharedInstance;
    
    SceneMap sceneMap;
    SceneTransforms sceneTransforms;
    std::shared_ptr<SceneClient> client;;
};

