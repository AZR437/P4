#include "TestDisplay.h"
#include "MeshManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "MeshObject.h"
#include "ShaderManager.h"
#include "TextureManager.h"
TestDisplay::TestDisplay() : AGameObject("TestDisplay")
{

}

TestDisplay::~TestDisplay()
{

}

void TestDisplay::initialize()
{

}

void TestDisplay::update()
{

}

void TestDisplay::draw()
{

}

void TestDisplay::onFinishedExecution(std::string objName)
{
	Mesh* mesh = MeshManager::getInstance()->getMesh(objName);
	VFShaders* shader = ShaderManager::getInstance()->getShaders("Simple");

	MeshObject* meshObject = new MeshObject(objName, mesh, shader, NULL, NULL);
	GameObjectManager::getInstance()->addObject(meshObject);
}
