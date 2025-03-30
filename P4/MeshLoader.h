#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "IWorkerAction.h"

class IExecutionEvent;

class MeshLoader : public IWorkerAction
{
public:
	MeshLoader(std::string path, IExecutionEvent* executionEvent);
	~MeshLoader();

public:
	virtual void onStartTask() override;

private:
	std::string path;
	IExecutionEvent* execEvent;
};

