#include "MeshManager.h"

//std::vector<GLfloat> MeshManager::load(std::string path) {
//    
//}

Mesh* MeshManager::getMesh(String meshName)
{
    if (this->meshMap.find(meshName) != this->meshMap.end())
        return this->meshMap[meshName];

    return NULL;
}

MeshManager* MeshManager::sharedInstance = NULL;

MeshManager* MeshManager::getInstance() {
    if (sharedInstance == NULL)
        sharedInstance = new MeshManager();

    return sharedInstance;
}
