#pragma once
#include <vector>
#include <glad/glad.h>

class VBO
{
private:
    GLuint vertexBuffer;

public:
    VBO();

public:
    void bufferData(std::vector<GLfloat> vertices);

public:
    void bind();
    void unbind();
    void deleteVertexBuffer();
};
