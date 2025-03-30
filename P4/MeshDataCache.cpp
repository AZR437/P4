#include "MeshDataCache.h"

MeshDataCache::MeshDataCache()
{

}

MeshDataCache::~MeshDataCache()
{
    for (int i = 0; i < this->cacheList.size(); i++)
    {
        delete this->cacheList[i];
    }

    this->cacheList.clear();
    this->cacheMap.clear();
}

void MeshDataCache::cacheMeshData(String path, const Data& data)
{
    this->guard.lock();
    Data* dataPtr = new Data(data);
    this->cacheList.push_back(dataPtr);
    this->cacheMap[path] = dataPtr;
    this->guard.unlock();
}

void MeshDataCache::deleteCachedData(String path)
{
    int index = -1;
    for (int i = 0; i < this->cacheList.size(); i++)
    {
        if (this->cacheList[i] == this->cacheMap[path])
        {
            index = i;
            break;
        }
    }

    if (index != -1) this->cacheList.erase(this->cacheList.begin() + index);

    delete this->cacheMap[path];
    this->cacheMap.erase(path);
}

MeshDataCache::Data* MeshDataCache::getMeshData(String path)
{
    if (this->cacheMap.find(path) != this->cacheMap.end())
        return this->cacheMap[path];

    return NULL;
}
