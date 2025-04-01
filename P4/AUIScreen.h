#pragma once
#include <string>
#include <imgui.h>

class UIManager;

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string getName();
	virtual void drawUI() = 0;

	std::string name;
	bool enabled = true;

	friend class UIManager;
};

