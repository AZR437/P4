#include "MeshDataCache.h"

MeshDataCache* MeshDataCache::sharedInstance = NULL;

MeshDataCache* MeshDataCache::getInstance()
{
    if (sharedInstance == NULL)
        sharedInstance = new MeshDataCache();

    return sharedInstance;
}

void MeshDataCache::cacheMeshData(String name, const Data& data)
{
    this->guard.lock();
    Data* dataPtr = new Data(data);
    this->cacheList.push_back(dataPtr);
    this->cacheMap[name] = dataPtr;
    this->guard.unlock();
}

void MeshDataCache::deleteCachedData(String name)
{
    int index = -1;
    for (int i = 0; i < this->cacheList.size(); i++)
    {
        if (this->cacheList[i] == this->cacheMap[name])
        {
            index = i;
            break;
        }
    }

    if (index != -1) this->cacheList.erase(this->cacheList.begin() + index);

    delete this->cacheMap[name];
    this->cacheMap.erase(name);
}

void MeshDataCache::deleteAllCachedData()
{
    for (int i = 0; i < this->cacheList.size(); i++)
    {
        delete this->cacheList[i];
    }

    this->cacheList.clear();
    this->cacheMap.clear();
}

MeshDataCache::Data* MeshDataCache::getMeshData(String name)
{
    if (this->cacheMap.find(name) != this->cacheMap.end())
        return this->cacheMap[name];

    return NULL;
}
