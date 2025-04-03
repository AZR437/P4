#include "ScenePickerScreen.h"
#include "iostream"
#include "SceneManager.h"
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
	if (ImGui::Button("Scene 1 Toggle", buttonSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_1")->getSceneObjects().empty())
		{
			this->scene1Enabled = !this->scene1Enabled;
			SceneManager::getInstance()->getScene("Scene_1")->setSceneObjectsEnabled(this->scene1Enabled);
		}
		else
		{
			std::cout << "Scene 1 has not been Loaded yet" << std::endl;
		}
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 2 Toggle", buttonSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_2")->getSceneObjects().empty())
		{
			this->scene2Enabled = !this->scene2Enabled;
			SceneManager::getInstance()->getScene("Scene_2")->setSceneObjectsEnabled(this->scene1Enabled);
		}
		else
		{
			std::cout << "Scene 2 has not been Loaded yet" << std::endl;
		}
	}
	
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 3 Toggle", buttonSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_3")->getSceneObjects().empty())
		{
			this->scene1Enabled = !this->scene1Enabled;
			SceneManager::getInstance()->getScene("Scene_3")->setSceneObjectsEnabled(this->scene3Enabled);
		}
		else
		{
			std::cout << "Scene 3 has not been Loaded yet" << std::endl;
		}
	}
	
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 4 Toggle", buttonSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_4")->getSceneObjects().empty())
		{
			this->scene4Enabled = !this->scene4Enabled;
			SceneManager::getInstance()->getScene("Scene_4")->setSceneObjectsEnabled(this->scene4Enabled);
		}
		else
		{
			std::cout << "Scene 4 has not been Loaded yet" << std::endl;
		}
	}
	
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 5 Toggle", buttonSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_5")->getSceneObjects().empty())
		{
			this->scene5Enabled = !this->scene5Enabled;
			SceneManager::getInstance()->getScene("Scene_5")->setSceneObjectsEnabled(this->scene5Enabled);
		}
		else
		{
			std::cout << "Scene 5 has not been Loaded yet" << std::endl;
		}
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Toggle All Scenes", buttonSize))
	{
		this->sceneAllEnabled = !this->sceneAllEnabled;
		for (int i = 1; i < 6; i++)
		{
			
			if (!SceneManager::getInstance()->getScene("Scene_" + std::to_string(i))->getSceneObjects().empty())
			{
				
				SceneManager::getInstance()->getScene("Scene_" + std::to_string(i))->setSceneObjectsEnabled(this->sceneAllEnabled);
			}
			else
			{
				std::cout << "Scene " << i << " has not been Loaded yet" << std::endl;
			}
		}
		
	}

	ImGui::EndTable();
	ImGui::End();
}
