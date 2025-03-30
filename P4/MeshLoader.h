#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "IWorkerAction.h"
#include "MeshDataCache.h"

class MeshLoader : public IWorkerAction
{
public:
	MeshLoader(std::string path, MeshDataCache* cache);
	~MeshLoader();

public:
	virtual void onStartTask() override;

private:
	std::string path;
	MeshDataCache* cache;
};

