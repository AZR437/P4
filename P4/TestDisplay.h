#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
class TestDisplay : public AGameObject, public IExecutionEvent
{
public:
	TestDisplay();
	~TestDisplay();

	void initialize() override;
	void update() override;
	void draw() override;


	void onFinishedExecution(std::string objName) override;



};

