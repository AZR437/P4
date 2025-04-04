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

	for (int i = 0; i < 6; i++)
	{
		ImGui::TableNextColumn();
		if (i < 5)
		{
			std::string buttonLabel = "Scene " + std::to_string(i + 1) + " Un/Load";
			if (ImGui::Button(buttonLabel.c_str(), cellSize))
			{
				if (!this->hasScene(i))
				{
					std::cout << "Start Load Scene " << i + 1 << std::endl;
					this->loadScene(i);
				}
				else
				{
					std::cout << "Destroying Scene " << i + 1 << std::endl;
					this->destroyScene(i);
				}
			}
		}
		else
		{
			if (ImGui::Button("Un/Load All Scenes", cellSize))
			{
				for (int j = 0; j < 5; j++)
				{
					this->sceneToggle[j] = this->sceneToggle[i];
					if (!this->hasScene(i))
					{
						std::cout << "Start Load Scene " << j + 1 << std::endl;
						this->loadScene(j);
					}
					else
					{
						std::cout << "Destroying Scene " << j + 1 << std::endl;
						this->destroyScene(j);
					}
				}
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		ImGui::TableNextColumn();
		if (i < 5)
		{
			std::string checkBoxLabel = "Scene " + std::to_string(i + 1) + " Toggle";
			if (ImGui::Checkbox(checkBoxLabel.c_str(), &this->sceneToggle[i]))
				this->toggleScene(i);
		}
		else
		{
			if (ImGui::Checkbox("Toggle All Scenes", &this->sceneToggle[i]))
			{
				for (int j = 0; j < 5; j++)
				{
					this->sceneToggle[j] = this->sceneToggle[i];
					this->toggleScene(j);
				}
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

void ScenePickerScreen::loadScene(unsigned int index)
{
	std::string sceneName = "Scene_" + std::to_string(index + 1);
	std::vector<AGameObject*> empty;
	SceneManager::getInstance()->createScene(sceneName, empty);
	this->client->LoadScene(sceneName);
}

bool ScenePickerScreen::hasScene(unsigned int index)
{
	std::string sceneName = "Scene_" + std::to_string(index + 1);
	return SceneManager::getInstance()->hasScene(sceneName);
}

void ScenePickerScreen::toggleScene(unsigned int index)
{
	std::string sceneName = "Scene_" + std::to_string(index + 1);
	if (!SceneManager::getInstance()->getScene(sceneName)->getSceneObjects().empty())
		SceneManager::getInstance()->getScene(sceneName)->setSceneObjectsEnabled(this->sceneToggle[index]);
	else std::cout << "Scene " << index + 1 << " has not been loaded yet" << std::endl;
}

void ScenePickerScreen::destroyScene(unsigned int index)
{
	std::string sceneName = "Scene_" + std::to_string(index + 1);
	SceneManager::getInstance()->destroyScene(sceneName, true);
}
