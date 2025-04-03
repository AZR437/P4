#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "IWorkerAction.h"
#include "MeshDataCache.h"

class IExecutionEvent;
class MeshLoaderAction : public IWorkerAction
{
public:
	MeshLoaderAction(
		std::string name,
		MeshDataCache* cache,
		IExecutionEvent* execEvent,
		std::string dataPath,
		bool isData
	);
	~MeshLoaderAction();

public:
	virtual void onStartTask() override;

private:
	std::string name;
	MeshDataCache* cache;
	IExecutionEvent* execEvent;

	std::string dataPath;
	bool isData;
};

