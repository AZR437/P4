#pragma once
#include <string>
#include <imgui.h>

class UIManager;

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string GetName();
	virtual void DrawUI() = 0;

	std::string name;
	bool enabled = true;

	friend class UIManager;
};

