#pragma once
#include "UINames.h"
#include "SceneClient.h"
class UIManager
{
public:
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<std::string, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(GLFWwindow* window, std::shared_ptr<SceneClient> client);
	static void destroy();
	void newFrame();
	void drawAllUI();

	AUIScreen* getUIScreen(std::string name);
	bool getEnabled(std::string name);
	void setEnabled(std::string name, bool enabled);

private:
	UIManager(GLFWwindow* window, std::shared_ptr<SceneClient> clientPtr);
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};

	static UIManager* instance;

	UIList uiList;
	UITable uiTable;
	std::shared_ptr<SceneClient> client;
};

