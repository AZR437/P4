#include "MeshLoaderAction.h"
#include "IExecutionEvent.h"
#include "MeshManager.h"
#include "MeshLoader.h"

MeshLoaderAction::MeshLoaderAction(
    std::string name,
    MeshDataCache* cache,
    IExecutionEvent* execEvent,
    std::string dataPath,
    bool isData
)
{
    this->name = name;
    this->cache = cache;
    this->execEvent = execEvent;
    this->dataPath = dataPath;
    this->isData = isData;
}

MeshLoaderAction::~MeshLoaderAction()
{

}

void MeshLoaderAction::onStartTask()
{
    std::vector<GLfloat> vertexData;

    if (this->isData)
    {
        if (MeshLoader::load(this->dataPath, &vertexData))
        {
            this->cache->cacheMeshData(this->name, vertexData);
            if (this->execEvent) this->execEvent->onFinishedExecution(this->name);
        }
    }
    else
    {
        if (MeshLoader::load(this->dataPath.c_str(), &vertexData))
        {
            this->cache->cacheMeshData(this->name, vertexData);
            if (this->execEvent) this->execEvent->onFinishedExecution(this->name);
        }
    }
    
    delete this;
}
