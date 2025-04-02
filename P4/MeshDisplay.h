#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
class MeshDisplay : public AGameObject, public IExecutionEvent
{
public:
	MeshDisplay();
	~MeshDisplay();

	void initialize() override;
	void update() override;
	void draw() override;

	void onFinishedExecution() override;


};

