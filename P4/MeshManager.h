#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "ThreadPool.h"

class IExecutionEvent;
class MeshDataCache;
class MeshManager
{
public:
    typedef std::string String;
    typedef std::unordered_map<String, Mesh*> HashTable;

    static MeshManager* getInstance();
    bool loadMeshData(
        String name,
        String dataPath,
        bool isData = false
    );
    void loadMeshDataAsync(
        String name,
        String dataPath,
        IExecutionEvent* execEvent,
        bool isData = false
    );
    void loadMeshFromCache(String name);
    Mesh* getMesh(String name);

private:
    MeshManager();
    ~MeshManager();
    MeshManager(const MeshManager&) {}
    MeshManager& operator = (const MeshManager&) {}
    static MeshManager* sharedInstance;

    HashTable meshMap;
    MeshDataCache* cache;
    ThreadPool* threadPool;
};
