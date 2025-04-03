#pragma once
#include <vector>
#include "VFShaders.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Plane
{
private:
    float vertices[12]{
        -1.f, 0.f,  1.f,
         1.f, 0.f,  1.f,
         1.f, 0.f, -1.f,
        -1.f, 0.f, -1.f,
    };

    unsigned int indices[6]{
        0,1,2,
        2,3,0,
    };

    VAO* vao;
    VBO* vbo;
    EBO* ebo;

public:
    Plane();
    ~Plane();
    void draw();

private:
    std::vector<GLfloat> getVertices();
    std::vector<GLuint> getIndices();

};

