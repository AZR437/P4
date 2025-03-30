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
    void draw();

public:
    void bind();
    void unbind();
    void deleteElementBuffer();
};
