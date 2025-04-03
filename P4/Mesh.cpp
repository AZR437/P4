#include "Mesh.h"
#include "iostream"
Mesh::Mesh(std::vector<GLfloat> vertices)
{
    this->vao = new VAO;
    this->vbo = new VBO;
    this->numVertices = vertices.size();
    std::cout << "Creating GPU Mesh with size: " << this->numVertices << "\n";
    int dimensions[]{ 3 };

    this->vao->bind();
    this->vbo->bind();

    this->vbo->bufferData(vertices);
    this->vao->createPointers(dimensions, 1);
    
    this->vbo->unbind();
    this->vao->unbind();
}

Mesh::~Mesh()
{
    this->vao->deleteVertexArray();
    this->vbo->deleteVertexBuffer();

    delete this->vao;
    delete this->vbo;
}

void Mesh::bind()
{
    this->vao->bind();
}

void Mesh::draw()
{
    this->vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, this->numVertices / 3);
}
