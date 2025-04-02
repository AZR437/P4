#include "Mesh.h"

Mesh::Mesh(VAO* vao, std::vector<GLfloat> vertices)
{
    this->vao = vao;
    this->vbo = new VBO;
    this->numVertices = vertices.size();

    this->vbo->bind();
    this->vbo->bufferData(vertices);
    this->vbo->unbind();
}

Mesh::~Mesh()
{
    this->vbo->deleteVertexBuffer();
    delete this->vbo;
}

void Mesh::bind()
{
    this->vao->bind();
}

void Mesh::draw()
{
    this->vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, this->numVertices / 14);
}
