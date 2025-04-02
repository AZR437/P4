#include "MeshLoader.h"
#include "IExecutionEvent.h"
#include "MeshManager.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

MeshLoader::MeshLoader(
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

MeshLoader::~MeshLoader()
{

}

void MeshLoader::onStartTask()
{
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    bool success = false;
    if (this->isData)
    {
        std::istringstream objStream(this->dataPath);
        success = tinyobj::LoadObj(
            &attributes,
            &shapes,
            &material,
            &warning,
            &error,
            &objStream
        );
    }
    else
    {
        success = tinyobj::LoadObj(
            &attributes,
            &shapes,
            &material,
            &warning,
            &error,
            this->dataPath.c_str()
        );
    }

    if (!success)
    {
        std::cout << error << std::endl;
    }
    else
    {
        std::vector<GLfloat> vertexData;

        for (int i = 0; i < shapes.size(); i++)
        {
            for (int j = 0; j < shapes[i].mesh.indices.size(); j++)
            {
                tinyobj::index_t vData1 = shapes[i].mesh.indices[j];
                tinyobj::index_t vData2 = shapes[i].mesh.indices[j + 1];
                tinyobj::index_t vData3 = shapes[i].mesh.indices[j + 2];

                //XYZ
                glm::vec3 v1 = glm::vec3(
                    attributes.vertices[vData1.vertex_index * 3],
                    attributes.vertices[vData1.vertex_index * 3 + 1],
                    attributes.vertices[vData1.vertex_index * 3 + 2]
                );
                glm::vec3 v2 = glm::vec3(
                    attributes.vertices[vData2.vertex_index * 3],
                    attributes.vertices[vData2.vertex_index * 3 + 1],
                    attributes.vertices[vData2.vertex_index * 3 + 2]
                );
                glm::vec3 v3 = glm::vec3(
                    attributes.vertices[vData3.vertex_index * 3],
                    attributes.vertices[vData3.vertex_index * 3 + 1],
                    attributes.vertices[vData3.vertex_index * 3 + 2]
                );

                //UV
                glm::vec2 uv1 = glm::vec2(
                    attributes.texcoords[vData1.texcoord_index * 2],
                    attributes.texcoords[vData1.texcoord_index * 2 + 1]
                );
                glm::vec2 uv2 = glm::vec2(
                    attributes.texcoords[vData2.texcoord_index * 2],
                    attributes.texcoords[vData2.texcoord_index * 2 + 1]
                );
                glm::vec2 uv3 = glm::vec2(
                    attributes.texcoords[vData3.texcoord_index * 2],
                    attributes.texcoords[vData3.texcoord_index * 2 + 1]
                );

                glm::vec3 deltaPos1 = v2 - v1;
                glm::vec3 deltaPos2 = v3 - v1;

                glm::vec2 deltaUV1 = uv2 - uv1;
                glm::vec2 deltaUV2 = uv3 - uv1;

                float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));

                glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
                glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

                vertexData.push_back(attributes.vertices[vData1.vertex_index * 3]);          //X
                vertexData.push_back(attributes.vertices[vData1.vertex_index * 3 + 1]);      //Y
                vertexData.push_back(attributes.vertices[vData1.vertex_index * 3 + 2]);      //Z

                vertexData.push_back(attributes.normals[vData1.normal_index * 3]);           //Normals X
                vertexData.push_back(attributes.normals[vData1.normal_index * 3 + 1]);       //Normals Y
                vertexData.push_back(attributes.normals[vData1.normal_index * 3 + 2]);       //Normals Z

                vertexData.push_back(attributes.texcoords[vData1.texcoord_index * 2]);       //U
                vertexData.push_back(attributes.texcoords[vData1.texcoord_index * 2 + 1]);   //V

                vertexData.push_back(tangent.x);
                vertexData.push_back(tangent.y);
                vertexData.push_back(tangent.z);

                vertexData.push_back(bitangent.x);
                vertexData.push_back(bitangent.y);
                vertexData.push_back(bitangent.z);
            }
        }

        this->cache->cacheMeshData(this->name, vertexData);
        MeshManager::getInstance()->loadMeshFromCache(this->name);
        if (this->execEvent) this->execEvent->onFinishedExecution();
    }

    delete this;
}
