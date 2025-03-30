#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class MeshDataCache
{
public:
    typedef std::string String;
    typedef std::vector<GLfloat> Data;
    typedef std::vector<Data*> CacheList;
    typedef std::unordered_map<String, Data*> HashTable;
    typedef std::mutex Mutex;

    MeshDataCache();
    ~MeshDataCache();

    void cacheMeshData(String path, const Data& data);
    void deleteCachedData(String path);

    Data* getMeshData(String path);

private:
    CacheList cacheList;
    HashTable cacheMap;
    Mutex guard;
};

