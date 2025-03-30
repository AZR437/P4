#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "ThreadPool.h"

class MeshDataCache;
class MeshManager
{
public:
    typedef std::string String;
    typedef std::unordered_map<String, Mesh*> HashTable;

    static MeshManager* getInstance();
    void loadMeshDataAsync(String path);
    void loadMeshFromCache(String path);
    Mesh* getMesh(String path);

private:
    MeshManager();
    ~MeshManager();
    MeshManager(const MeshManager&) {}
    MeshManager& operator = (const MeshManager&) {}
    static MeshManager* sharedInstance;

    HashTable meshMap;
    MeshDataCache* cache;
    ThreadPool* threadPool;
    VAO* vao;
};
