#pragma once
#include "AUIScreen.h"
class ProfilerScreen : public AUIScreen
{
protected:
	ProfilerScreen();
	~ProfilerScreen();
	virtual void drawUI() override;

	friend class UIManager;

private:
	double ticks = 0.0;
	int fps = 0;
};

