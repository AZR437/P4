#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include <queue>
class MeshDisplay : public AGameObject, public IExecutionEvent
{
public:
	MeshDisplay();
	~MeshDisplay();

	void initialize() override;
	void update() override;
	void draw() override;


	void onFinishedExecution(std::string objName) override;

private:
	float ticks = 0.0f;
	float loadDelay = 0.5f;
	std::queue<std::string> loadQueue;

};

