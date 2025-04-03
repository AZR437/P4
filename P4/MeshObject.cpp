#include "MeshObject.h"
#include "CameraManager.h"
#include "LightManager.h"

MeshObject::MeshObject(String name, Mesh* mesh, VFShaders* shaders, GLuint* texture, GLuint* normalMap) : AGameObject(name)
{
    this->mesh = mesh;
    this->shaders = shaders;
    this->texture = texture;
    this->normalMap = normalMap;
    this->scale(10);
}

MeshObject::~MeshObject()
{

}

void MeshObject::initialize()
{
}

void MeshObject::update()
{

}

void MeshObject::draw()
{
    Camera* cam = CameraManager::getInstance()->getCamera();
    this->shaders->setMat4("transform", this->transformation);
    this->shaders->setMat4("view", cam->getView());
    this->shaders->setMat4("projection", cam->getProjection());
    this->shaders->setVec3("cameraPos", cam->getPosition());
    this->shaders->setLights(LightManager::getInstance()->getLights());

    bool hasTexture = this->texture != NULL;
    this->shaders->setBool("hasTexture", hasTexture);
    if (hasTexture) this->shaders->setTexture("tex0", this->texture, GL_TEXTURE0, GL_TEXTURE_2D, 0);

    bool hasNormal = this->normalMap != NULL;
    this->shaders->setBool("hasNormal", hasNormal);
    if (hasNormal) this->shaders->setTexture("normTex", this->normalMap, GL_TEXTURE1, GL_TEXTURE_2D, 1);

    this->mesh->draw();
}
