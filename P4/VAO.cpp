#include "VAO.h"
#include <iostream>

VAO::VAO() {
    glGenVertexArrays(1, &this->vertexArray);
}

void VAO::createPointers(int dimensions[], int attribs) {
    int totalAttribs = 0;
    for (int i = 0; i < attribs; i++) {
        totalAttribs += dimensions[i];
    }

    int usedAttribs = 0;
    for (int i = 0; i < attribs; i++) {
        GLintptr newPointer = usedAttribs * sizeof(float);
        glVertexAttribPointer(
            i,
            dimensions[i],
            GL_FLOAT,
            GL_FALSE,
            totalAttribs * sizeof(float),
            (void*)newPointer
        );
        glEnableVertexAttribArray(i);
        usedAttribs += dimensions[i];
    }

    GLenum err;
    if (err = glGetError() != GL_NO_ERROR)
        std::cout << "Error generating vertex attrib pointers: " << err << "\n";
}

void VAO::bind() {
    glBindVertexArray(this->vertexArray);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::deleteVertexArray() {
    glDeleteBuffers(1, &this->vertexArray);
}