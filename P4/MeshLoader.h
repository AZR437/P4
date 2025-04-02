#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "IWorkerAction.h"
#include "MeshDataCache.h"

class IExecutionEvent;
class MeshLoader : public IWorkerAction
{
public:
	MeshLoader(
		std::string name,
		MeshDataCache* cache,
		IExecutionEvent* execEvent,
		std::string dataPath,
		bool isData
	);
	~MeshLoader();

public:
	virtual void onStartTask() override;

private:
	std::string name;
	MeshDataCache* cache;
	IExecutionEvent* execEvent;

	std::string dataPath;
	bool isData;
};

