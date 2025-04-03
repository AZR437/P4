#include "ScenePickerScreen.h"
#include "iostream"
ScenePickerScreen::ScenePickerScreen(std::shared_ptr<SceneClient> client) : AUIScreen("SCENE_PICKER_SCREEN")
{
	this->client = client;
}

ScenePickerScreen::~ScenePickerScreen()
{
	
}

void ScenePickerScreen::drawUI()
{
	ImGui::Begin("Scene Picker", &this->enabled, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::BeginTable("Scene Table", 5);
	ImVec2 buttonSize = ImVec2(120, 20);
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 1 Load", buttonSize))
	{
		std::cout << "Start Load Scene 1" << std::endl;
		this->client->LoadScene("Scene_1");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 2 Load", buttonSize))
	{
		std::cout << "Start Load Scene 2" << std::endl;
		this->client->LoadScene("Scene_2");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 3 Load", buttonSize))
	{
		std::cout << "Start Load Scene 3" << std::endl;
		this->client->LoadScene("Scene_3");
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 4 Load", buttonSize))
	{
		std::cout << "Start Load Scene 4" << std::endl;
		this->client->LoadScene("Scene_4");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 5 Load", buttonSize))
	{
		std::cout << "click Scene 5" << std::endl;
		this->client->LoadScene("Scene_1");
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Load all", buttonSize))
	{
		std::cout << "click scene load all" << std::endl;
		this->client->LoadScene("Scene_1");
	}

	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	ImGui::Button("Scene 1 Loaded", buttonSize);

	ImGui::TableNextColumn();
	ImGui::Button("Scene 2 Loaded", buttonSize);
	
	ImGui::TableNextColumn();
	ImGui::Button("Scene 3 Loaded", buttonSize);
	
	ImGui::TableNextColumn();
	ImGui::Button("Scene 4 Loaded", buttonSize);
	
	ImGui::TableNextColumn();
	ImGui::Button("Scene 5 Loaded", buttonSize);

	ImGui::EndTable();
	ImGui::End();
}
