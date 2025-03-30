#include "Mesh.h"

Mesh::Mesh(VAO* vao, std::vector<GLfloat> vertices)
{
    this->vao = vao;
    this->vbo = new VBO;
    this->numVertices = vertices.size();
    this->ebo = new EBO;

    this->vbo->bind();
    this->ebo->bind();

    this->vbo->bufferData(vertices);
    //this->ebo->bufferData();

    this->vbo->unbind();
    //this->ebo->unbind();
}

Mesh::~Mesh()
{

}

void Mesh::draw()
{
    this->vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, this->numVertices / 14);
}
