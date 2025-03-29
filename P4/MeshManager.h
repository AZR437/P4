#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class MeshManager
{
public:
    static MeshManager* getInstance();
    std::vector<GLfloat> load(std::string path);

private:
    MeshManager() {}
    MeshManager(const MeshManager&) {}
    MeshManager& operator = (const MeshManager&) {}
    static MeshManager* sharedInstance;
};
