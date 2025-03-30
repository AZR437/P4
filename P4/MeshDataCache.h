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

    static MeshDataCache* getInstance();
    void cacheMeshData(String name, const Data& data);
    void deleteCachedData(String name);
    void deleteAllCachedData();

    Data* getMeshData(String name);

private:
    MeshDataCache() {}
    MeshDataCache(const MeshDataCache&) {}
    MeshDataCache& operator = (const MeshDataCache&) {}
    static MeshDataCache* sharedInstance;

    CacheList cacheList;
    HashTable cacheMap;
    Mutex guard;
};

