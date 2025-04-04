#include "VBO.h"
#include <iostream>

VBO::VBO() {
    glGenBuffers(1, &this->vertexBuffer);
}

void VBO::bufferData(std::vector<GLfloat> vertices) {
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * vertices.size(),
        vertices.data(),
        GL_STATIC_DRAW
    );

    GLenum err;
    if (err = glGetError() != GL_NO_ERROR)
        std::cout << "Error generating buffer data: " << err << "\n";
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVertexBuffer() {
    glDeleteBuffers(1, &this->vertexBuffer);
}