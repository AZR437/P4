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
	std::vector<AGameObject*> empty;
	for (int i = 1; i < 6; i++)
	{
		SceneManager::getInstance()->createScene("Scene_" + std::to_string(i), empty);
	}
	
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
	VFShaders* shader = ShaderManager::getInstance()->getShaders("Default");

	MeshObject* meshObject = new MeshObject(objName, mesh, shader, NULL, NULL);
	meshObject->translate(transforms.getPosX(), transforms.getPosY(), transforms.getPosZ());
	meshObject->scale(transforms.getScaleX(), transforms.getScaleY(), transforms.getScaleZ());
	SceneManager::getInstance()->getScene(transforms.getSceneName())->registerSceneObject(meshObject);
	
	GameObjectManager::getInstance()->addObject(meshObject);
}
