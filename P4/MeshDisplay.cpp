#include "MeshDisplay.h"
#include "MeshManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "MeshObject.h"
#include "ShaderManager.h"
#include "TextureManager.h"
MeshDisplay::MeshDisplay() : AGameObject("MeshDisplay")
{
}

MeshDisplay::~MeshDisplay()
{

}

void MeshDisplay::initialize()
{
	
}

void MeshDisplay::update()
{

}

void MeshDisplay::draw()
{

}





void MeshDisplay::onFinishedExecution(std::string objName)
{
	SceneObjTransforms transforms = SceneManager::getInstance()->getObjTransforms(objName);
	Mesh* mesh = MeshManager::getInstance()->getMesh(objName);
	VFShaders* shader = ShaderManager::getInstance()->getShaders("Simple");

	MeshObject* meshObject = new MeshObject(objName, mesh, shader, NULL, NULL);
	meshObject->translate(transforms.getPosX(), transforms.getPosY(), transforms.getPosZ());
	meshObject->scale(transforms.getScaleX(), transforms.getScaleY(), transforms.getScaleZ());

	auto scene = SceneManager::getInstance()->getScene(transforms.getSceneName());
	if (!scene) {
		std::cerr << "Error: Scene not found for " << transforms.getSceneName() << std::endl;
	}

	SceneManager::getInstance()->getScene(transforms.getSceneName())->registerSceneObject(meshObject);
	GameObjectManager::getInstance()->addObject(meshObject);
}
