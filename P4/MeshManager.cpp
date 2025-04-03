#include "MeshManager.h"
#include "MeshLoader.h"

Mesh* MeshManager::getMesh(String meshName)
{
    if (this->meshMap.find(meshName) != this->meshMap.end())
        return this->meshMap[meshName];

    return NULL;
}

MeshManager::MeshManager()
{
    this->cache = new MeshDataCache();
    this->vao = new VAO();
    this->threadPool = new ThreadPool("MeshLoaderPool", 8);
    this->threadPool->startScheduler();

    int dimensions[]{ 3,3,2,3,3 };
    this->vao->bind();
    this->vao->createPointers(dimensions, 5);
    this->vao->unbind();
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

void MeshManager::loadMeshDataAsync(
    String name,
    String dataPath,
    IExecutionEvent* execEvent,
    bool isData
)
{
    MeshLoader* meshLoader = new MeshLoader(name, this->cache, execEvent, dataPath, isData);
    this->threadPool->scheduleTask(meshLoader);
}

void MeshManager::loadMeshFromCache(String path)
{
    if (this->meshMap.find(path) != this->meshMap.end())
    {
        std::cout << "[MeshManager] WARNING: Mesh already exists." << "\n";
    }
    else
    {
        Mesh* mesh = new Mesh(this->vao, *this->cache->getMeshData(path));
        this->meshMap[path] = mesh;
        std::cout << "[MeshManager] Mesh loaded: " << path << "\n";
    }
}
