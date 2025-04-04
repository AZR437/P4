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
	ImGui::Begin("Scene Picker", &this->enabled, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::BeginTable("Scene Table", 6);
	ImVec2 cellSize = ImVec2(150, 20);

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 1 Load", cellSize))
	{
		std::cout << "Start Load Scene 1" << std::endl;
		this->client->LoadScene("Scene_1");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 2 Load", cellSize))
	{
		std::cout << "Start Load Scene 2" << std::endl;
		this->client->LoadScene("Scene_2");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 3 Load", cellSize))
	{
		std::cout << "Start Load Scene 3" << std::endl;
		this->client->LoadScene("Scene_3");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 4 Load", cellSize))
	{
		std::cout << "Start Load Scene 4" << std::endl;
		this->client->LoadScene("Scene_4");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 5 Load", cellSize))
	{
		std::cout << "click Scene 5" << std::endl;
		this->client->LoadScene("Scene_5");
	}

	ImGui::TableNextColumn();
	if (ImGui::Button("Load all", cellSize))
	{
		std::cout << "click scene load all" << std::endl;
		for (int i = 1; i < 6; i++)
		{
			this->client->LoadScene("Scene_" + std::to_string(i));
		}
	}

	for (int i = 0; i < 6; i++)
	{
		std::string checkBoxLabel = "Scene " + std::to_string(i + 1) + " Toggle";
		ImGui::TableNextColumn();
		if (ImGui::Checkbox(checkBoxLabel.c_str(), &this->sceneToggle[i]))
		{
			if (i < 5)
			{
				std::string checkBoxLabel = "Scene_" + std::to_string(i + 1);
				if (!SceneManager::getInstance()->getScene("Scene_1")->getSceneObjects().empty())
					SceneManager::getInstance()->getScene("Scene_1")->setSceneObjectsEnabled(this->sceneToggle[i]);
				else std::cout << "Scene " << i + 1 << " has not been Loaded yet" << std::endl;
			}
			else
			{
				for (int j = 0; j < 5; j++)
				{
					this->sceneToggle[j + 1] = this->sceneToggle[i];
					if (!SceneManager::getInstance()->getScene("Scene_" + std::to_string(j + 1))->getSceneObjects().empty())
						SceneManager::getInstance()->getScene("Scene_" + std::to_string(j + 1))->setSceneObjectsEnabled(this->sceneToggle[j + 1]);
					else std::cout << "Scene " << j + 1 << " has not been Loaded yet" << std::endl;
				}
			}
		}
	}
	
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 1 Unload", cellSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_1")->getSceneObjects().empty())
		{
			SceneManager::getInstance()->destroyScene("Scene_1", true);
		}
		else
		{
			std::cout << "Scene 1 has not been Loaded yet" << std::endl;
		}
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 2 Unload", cellSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_2")->getSceneObjects().empty())
		{
			SceneManager::getInstance()->destroyScene("Scene_2", true);
		}
		else
		{
			std::cout << "Scene 2 has not been Loaded yet" << std::endl;
		}
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 3 Unload", cellSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_3")->getSceneObjects().empty())
		{
			SceneManager::getInstance()->destroyScene("Scene_3", true);
		}
		else
		{
			std::cout << "Scene 3 has not been Loaded yet" << std::endl;
		}
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 4 Unload", cellSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_4")->getSceneObjects().empty())
		{
			SceneManager::getInstance()->destroyScene("Scene_4", true);
		}
		else
		{
			std::cout << "Scene 4 has not been Loaded yet" << std::endl;
		}
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Scene 5 Unload", cellSize))
	{
		if (!SceneManager::getInstance()->getScene("Scene_5")->getSceneObjects().empty())
		{
			SceneManager::getInstance()->destroyScene("Scene_5", true);
		}
		else
		{
			std::cout << "Scene 5 has not been Loaded yet" << std::endl;
		}
	}
	ImGui::TableNextColumn();
	if (ImGui::Button("Unload All Scenes", cellSize))
	{
		for (int i = 1; i < 6; i++)
		{
			if (!SceneManager::getInstance()->getScene("Scene_" + std::to_string(i))->getSceneObjects().empty())
			{
				SceneManager::getInstance()->destroyScene("Scene_" + std::to_string(i), true);
			}
			else
			{
				std::cout << "Scene " << i << " has not been Loaded yet" << std::endl;
			}
		}
	}
	
	for (int i = 0; i < 5; i++)
	{
		ImGui::TableNextColumn();
		ImGui::ProgressBar(this->progress[i], cellSize);
	}
	
	ImGui::EndTable();
	ImGui::End();
	
}
