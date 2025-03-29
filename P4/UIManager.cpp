#include "UIManager.h"
#include "CustomStyles.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include "../GraphicsEngine/GraphicsEngine.h"
//#include "ProfilerScreen.h"
//#include "MenuScreen.h"
//#include "InspectorScreen.h"
//#include "OutlinerScreen.h"
//#include "CameraViewportScreen.h"
//#include "CreditsScreen.h"
//#include "ColorPickerScreen.h"
//#include "ScenePlayOptionsScreen.h"
//#include "ActionsScreen.h"
//#include "ConsoleScreen.h"
//#include "HUDScreen.h"

UIManager* UIManager::instance = NULL;

void UIManager::initialize(GLFWwindow* window)
{
	instance = new UIManager(window);
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
			this->uiList[i]->DrawUI();
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

UIManager::UIManager(GLFWwindow* window)
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

	//HUDScreen* hudScreen = new HUDScreen();
	//this->uiTable[uiNames.HUD_SCREEN] = hudScreen;
	//this->uiList.push_back(hudScreen);

	//ProfilerScreen* profilerScreen = new ProfilerScreen();
	//this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	//this->uiList.push_back(profilerScreen);

	//OutlinerScreen* outlinerScreen = new OutlinerScreen();
	//this->uiTable[uiNames.OUTLINER_SCREEN] = outlinerScreen;
	//this->uiList.push_back(outlinerScreen);

	//InspectorScreen* inspectorScreen = new InspectorScreen();
	//this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	//this->uiList.push_back(inspectorScreen);

	//CameraViewportScreen* cameraViewportScreen = new CameraViewportScreen();
	//this->uiTable[uiNames.CAMERA_VIEWPORT_SCREEN] = cameraViewportScreen;
	//this->uiList.push_back(cameraViewportScreen);

	//CreditsScreen* creditsScreen = new CreditsScreen();
	//this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	//this->uiList.push_back(creditsScreen);

	//ColorPickerScreen* colorPickerScreen = new ColorPickerScreen();
	//this->uiTable[uiNames.COLOR_PICKER_SCREEN] = colorPickerScreen;
	//this->uiList.push_back(colorPickerScreen);
	//
	//ScenePlayOptionsScreen* scenePlayOptionsScreen = new ScenePlayOptionsScreen();
	//this->uiTable[uiNames.SCENE_PLAY_OPTIONS_SCREEN] = scenePlayOptionsScreen;
	//this->uiList.push_back(scenePlayOptionsScreen);
	//
	//ActionsScreen* actionsScreen = new ActionsScreen();
	//this->uiTable[uiNames.ACTIONS_SCREEN] = actionsScreen;
	//this->uiList.push_back(actionsScreen);
	//
	//ConsoleScreen* consoleScreen = new ConsoleScreen();
	//this->uiTable[uiNames.CONSOLE_SCREEN] = consoleScreen;
	//this->uiList.push_back(consoleScreen);	
}

UIManager::~UIManager()
{

}
