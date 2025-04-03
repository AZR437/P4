#pragma once
#include <vector>
#include "VFShaders.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Skybox
{
private:
    float vertices[24]{
        -1.f, -1.f,  1.f,
         1.f, -1.f,  1.f,
         1.f, -1.f, -1.f,
        -1.f, -1.f, -1.f,
        -1.f,  1.f,  1.f,
         1.f,  1.f,  1.f,
         1.f,  1.f, -1.f,
        -1.f,  1.f, -1.f
    };

    unsigned int indices[36]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    VFShaders* shaders;
    GLuint* texture;

public:
    Skybox(VFShaders* shaders, GLuint* texture);
    ~Skybox();
    void draw();

    void setShaders(VFShaders* Shaders);

private:
    std::vector<GLfloat> getVertices();
    std::vector<GLuint> getIndices();

};