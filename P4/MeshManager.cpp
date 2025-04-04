#include "MeshManager.h"
#include "MeshLoader.h"
#include "MeshLoaderAction.h"

Mesh* MeshManager::getMesh(String name)
{
    if (this->meshMap.find(name) != this->meshMap.end())
        return this->meshMap[name];

    return NULL;
}

MeshManager::MeshManager()
{
    this->cache = new MeshDataCache();
    this->threadPool = new ThreadPool("MeshLoaderPool", 8);
    this->threadPool->startScheduler();
}

MeshManager::~MeshManager()
{
    this->threadPool->stopScheduler();

    delete this->threadPool;
    delete this->cache;
}

MeshManager* MeshManager::sharedInstance = NULL;

MeshManager* MeshManager::getInstance() {
    if (sharedInstance == NULL)
        sharedInstance = new MeshManager();

    return sharedInstance;
}

bool MeshManager::loadMeshData(String name, String dataPath, bool isData)
{
    std::vector<GLfloat> vertexData;
    if (MeshLoader::load(dataPath, &vertexData))
    {
        Mesh* mesh = new Mesh(vertexData);
        this->meshMap[name] = mesh;
        std::cout << "[MeshManager] Mesh loaded: " << name << "\n";
        return true;
    }
    return false;
}

void MeshManager::loadMeshDataAsync(
    String name,
    String dataPath,
    IExecutionEvent* execEvent,
    bool isData
)
{
    MeshLoaderAction* meshLoaderAction = new MeshLoaderAction(name, this->cache, execEvent, dataPath, isData);
    this->threadPool->scheduleTask(meshLoaderAction);
}

void MeshManager::loadMeshFromCache(String name)
{
    if (this->meshMap.find(name) != this->meshMap.end())
    {
        std::cout << "[MeshManager] WARNING: Mesh "<<name<< " already exists." << "\n";
    }
    else
    {
        Mesh* mesh = new Mesh(*this->cache->getMeshData(name));
        this->meshMap[name] = mesh;
        std::cout << "[MeshManager] Mesh loaded: " << name << "\n";
    }
}

void MeshManager::deleteMeshFromCache(String name)
{
    auto it = this->meshMap.find(name);

    if (it != this->meshMap.end()) {  
        delete it->second; 
        this->meshMap.erase(it);
        std::cout << "[MeshManager] Mesh deleted: " << name << "\n";
    }
}
