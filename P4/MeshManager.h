#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"

class MeshManager
{
public:
    typedef std::string String;
    typedef std::unordered_map<String, Mesh*> HashTable;

    static MeshManager* getInstance();
    //std::vector<GLfloat> load(std::string path);
    Mesh* getMesh(String meshName);

private:
    MeshManager() {}
    MeshManager(const MeshManager&) {}
    MeshManager& operator = (const MeshManager&) {}
    static MeshManager* sharedInstance;

    HashTable meshMap;
};
