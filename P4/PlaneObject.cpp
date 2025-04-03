#include "PlaneObject.h"
#include "CameraManager.h"

PlaneObject::PlaneObject(String name, VFShaders* shaders) : AGameObject(name)
{
    this->plane = new Plane();
    this->shaders = shaders;
}

PlaneObject::~PlaneObject()
{
    delete this->plane;
}

void PlaneObject::initialize()
{

}

void PlaneObject::update()
{

}

void PlaneObject::draw()
{

    Camera* cam = CameraManager::getInstance()->getCamera();
    this->shaders->setMat4("transform", this->transformation);
    this->shaders->setMat4("view", cam->getView());
    this->shaders->setMat4("projection", cam->getProjection());
    this->shaders->setVec3("cameraPos", cam->getPosition());
    //this->shaders->setLights(LightManager::getInstance()->getLights());
    this->shaders->setBool("hasTexture", false);
    this->shaders->setBool("hasNormal", false);

	this->plane->draw();
}
