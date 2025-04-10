#include "UIManager.h"
#include "CustomStyles.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "MenuScreen.h"
#include "ProfilerScreen.h"
#include "ScenePickerScreen.h"
#include "SceneClient.h"

UIManager* UIManager::instance = NULL;

UIManager* UIManager::getInstance()
{
	return instance;
}

void UIManager::initialize(GLFWwindow* window, std::shared_ptr<SceneClient> clientPtr)
{
	instance = new UIManager(window, clientPtr);
}

void UIManager::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (!instance->uiList.empty())
	{
		for (int i = instance->uiList.size() - 1; i >= 0; i--)
			delete instance->uiList[i];

		instance->uiTable.clear();
		instance->uiList.clear();
	}

	delete instance;
}

void UIManager::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UIManager::drawAllUI()
{
	for (int i = 0; i < this->uiList.size(); i++)
	{
		if (this->uiList[i]->enabled)
			this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

AUIScreen* UIManager::getUIScreen(std::string name)
{
	return this->uiTable[name];
}

bool UIManager::getEnabled(std::string name)
{
	AUIScreen* ui = this->uiTable[name];
	return ui ? ui->enabled : false;
}

void UIManager::setEnabled(std::string name, bool enabled)
{
	AUIScreen* ui = this->uiTable[name];
	if (ui) ui->enabled = enabled;
}

UIManager::UIManager(GLFWwindow* window, std::shared_ptr<SceneClient> clientPtr)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	CustomStyles styles;
	styles.StyleColorsCrimson();

	UINames uiNames;

	//MenuScreen* menuScreen = new MenuScreen();
	//this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	//this->uiList.push_back(menuScreen);
	 
	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	this->client = clientPtr;
	ScenePickerScreen* scenePickerScreen = new ScenePickerScreen(client);
	this->uiTable[uiNames.SCENE_PICKER_SCREEN] = scenePickerScreen;
	this->uiList.push_back(scenePickerScreen);


}
