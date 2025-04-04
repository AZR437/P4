#include "TestDisplay.h"
#include "MeshManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "MeshObject.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Time.h"
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
	this->ticks += Time::getUnscaledDeltaTime();
	if (this->ticks > this->loadDelay)
	{
		this->ticks = 0.0f;
		if (!this->loadQueue.empty())
		{
			std::string objName = this->loadQueue.front();
			this->loadQueue.pop();
			MeshManager::getInstance()->loadMeshFromCache(objName);
			Mesh* mesh = MeshManager::getInstance()->getMesh(objName);
			VFShaders* shader = ShaderManager::getInstance()->getShaders("Simple");

			MeshObject* meshObject = new MeshObject(objName, mesh, shader, NULL, NULL);
			GameObjectManager::getInstance()->addObject(meshObject);
		}
	}
}

void TestDisplay::draw()
{

}

void TestDisplay::onFinishedExecution(std::string objName)
{
	this->loadQueue.push(objName);
}
