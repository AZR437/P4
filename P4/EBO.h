#pragma once
#include <vector>
#include <glad/glad.h>

class EBO
{
private:
    GLuint elementBuffer;

public:
    EBO();

public:
    void bufferData(std::vector<GLuint> elements);

public:
    void bind();
    void unbind();
    void deleteElementBuffer();
};
