#include "MeshLoader.h"
#include "IExecutionEvent.h"
#include "MeshManager.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

bool MeshLoader::load(const char* path, std::vector<GLfloat>* vertexData)
{
    std::cout << "[MeshLoader] Loading mesh from path: " << path << "\n";
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path
    );

    if (!success)
    {
        std::cout << "Warning:" << warning << std::endl;
        std::cout << "Error: " << error << std::endl;
    }
    else
    {
        std::vector<GLfloat> vertices;

        for (int i = 0; i < shapes.size(); i++)
        {
            for (int j = 0; j < shapes[i].mesh.indices.size(); j++)
            {
                tinyobj::index_t vData1 = shapes[i].mesh.indices[j];

                vertices.push_back(attributes.vertices[vData1.vertex_index * 3]);         //X
                vertices.push_back(attributes.vertices[vData1.vertex_index * 3 + 1]);     //Y
                vertices.push_back(attributes.vertices[vData1.vertex_index * 3 + 2]);     //Z
            }
        }
        *vertexData = vertices;
        return true;
    }

    return false;
}

bool MeshLoader::load(String data, std::vector<GLfloat>* vertexData)
{
    std::cout << "[MeshLoader] Loading mesh with data" << "\n";
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    std::istringstream objStream(data);
    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        &objStream
    );

    if (!success)
    {
        std::cout << "Warning:" << warning << std::endl;
        std::cout << "Error: " << error << std::endl;
    }
    else
    {
        std::vector<GLfloat> vertices;

        for (int i = 0; i < shapes.size(); i++)
        {
            for (int j = 0; j < shapes[i].mesh.indices.size(); j++)
            {
                tinyobj::index_t vData1 = shapes[i].mesh.indices[j];

                vertices.push_back(attributes.vertices[vData1.vertex_index * 3]);         //X
                vertices.push_back(attributes.vertices[vData1.vertex_index * 3 + 1]);     //Y
                vertices.push_back(attributes.vertices[vData1.vertex_index * 3 + 2]);     //Z
            }
        }
        *vertexData = vertices;
        return true;
    }

    return false;
}
