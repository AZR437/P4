#include "Skybox.h"
#include "iostream"
#include "CameraManager.h"

Skybox::Skybox(VFShaders* shaders, GLuint* texture) {
    this->texture = texture;
    this->shaders = shaders;

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

Skybox::~Skybox()
{
    this->vao->deleteVertexArray();
    this->vbo->deleteVertexBuffer();
    this->ebo->deleteElementBuffer();

    delete this->vao;
    delete this->vbo;
    delete this->ebo;
}

void Skybox::draw() {
    Camera* cam = CameraManager::getInstance()->getCamera();
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat4(glm::mat3(cam->getView()));

    this->shaders->setMat4("projection", cam->getProjection());
    this->shaders->setMat4("view", view);

    this->vao->bind();

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *this->texture);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void Skybox::setShaders(VFShaders* shaders) {
    this->shaders = shaders;
}

std::vector<GLfloat> Skybox::getVertices() {
    std::vector<GLfloat> vertices;
    for (int i = 0; i < 24; i++) {
        vertices.push_back(this->vertices[i]);
    }
    return vertices;
}

std::vector<GLuint> Skybox::getIndices() {
    std::vector<GLuint> indices;
    for (int i = 0; i < 36; i++) {
        indices.push_back(this->indices[i]);
    }
    return indices;
}