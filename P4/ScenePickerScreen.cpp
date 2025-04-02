#include "ScenePickerScreen.h"

ScenePickerScreen::ScenePickerScreen() : AUIScreen("SCENE_PICKER_SCREEN")
{

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
	ImGui::Button("Scene 1", buttonSize);

	ImGui::TableNextColumn();
	ImGui::Button("Scene 2", buttonSize);

	ImGui::TableNextColumn();
	ImGui::Button("Scene 3", buttonSize);

	ImGui::TableNextColumn();
	ImGui::Button("Scene 4", buttonSize);

	ImGui::TableNextColumn();
	ImGui::Button("Scene 5", buttonSize);

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
