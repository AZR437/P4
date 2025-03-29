#pragma once
#include <glad/glad.h>

class VAO
{
private:
    GLuint vertexArray;

public:
    VAO();

public:
    void createPointers(int dimensions[], int attribs);

public:
    void bind();
    void unbind();
    void deleteVertexArray();
};
