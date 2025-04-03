#include "Plane.h"
#include "iostream"
#include "CameraManager.h"
#include "LightManager.h"

Plane::Plane()
{
    int dims[]{ 3 };

    this->vao = new VAO;
    this->vbo = new VBO;
    this->ebo = new EBO;

    this->vao->bind();

    this->vbo->bind();
    this->vbo->bufferData(this->getVertices());
    this->vao->createPointers(dims, 1);

    this->ebo->bind();
    this->ebo->bufferData(this->getIndices());

    this->vao->unbind();
}

Plane::~Plane()
{
    this->vao->deleteVertexArray();
    this->vbo->deleteVertexBuffer();
    this->ebo->deleteElementBuffer();

    delete this->vao;
    delete this->vbo;
    delete this->ebo;
}

void Plane::draw()
{
    this->vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

std::vector<GLfloat> Plane::getVertices()
{
    std::vector<GLfloat> vertices;
    for (int i = 0; i < 12; i++)
    {
        vertices.push_back(this->vertices[i]);
    }
    return vertices;
}

std::vector<GLuint> Plane::getIndices()
{
    std::vector<GLuint> indices;
    for (int i = 0; i < 6; i++)
    {
        indices.push_back(this->indices[i]);
    }
    return indices;
}