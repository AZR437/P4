#include "MenuScreen.h"
#include "UIManager.h"

#include "filesystem"

MenuScreen::MenuScreen() : AUIScreen("MENU_SCREEN")
{
	
}

MenuScreen::~MenuScreen()
{

}

void MenuScreen::drawUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
	if (ImGui::BeginMainMenuBar())
	{
		//ImGui::DockSpaceOverViewport();

		if (ImGui::BeginMenu("File"))
		{
			this->showMenuFile();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game Object"))
		{
			this->showMenuGameObject();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			this->showMenuWindow();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("About"))
		{
			this->showMenuAbout();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scene Cameras"))
		{
			this->showMenuScreenCameras();
			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
	
	ImGui::PopStyleVar();
	}

	if (this->openFileDialogue)
	{
		this->openFileDialogue = false;
		ImGui::OpenPopup("Save Scene As:");
	}

	this->showFileDialogue();
}

void MenuScreen::showMenuFile()
{
	if (ImGui::MenuItem("New Scene", "Ctrl+N"))
	{
		//GameObjectManager::DeleteAllGameObjects();
	}

	if (ImGui::MenuItem("Open Scene", "Ctrl+O"))
	{
		//SaveSystem::GetInstance()->LoadScene("NewSave.level");
	}

	if (ImGui::BeginMenu("Open Recent Scene"))
	{
		this->showMenuOpenRecentScene();
		ImGui::EndMenu();
	}

	ImGui::Separator();

	if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
	{
		/*if (SaveSystem::GetInstance()->IsSceneOpen())
			SaveSystem::GetInstance()->SaveToCurrent();
		else this->openFileDialogue = true;*/
	}

	if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
	{
		this->openFileDialogue = true;
	}

	ImGui::Separator();

	if (ImGui::MenuItem("Project Settings..."))
	{
		
	}
}

void MenuScreen::showMenuGameObject()
{
	if (ImGui::MenuItem("Create Sphere"))
	{
		//GameObjectManager::CreateGameObject(SPHERE);
	}

	if (ImGui::MenuItem("Create Capsule"))
	{
		//GameObjectManager::CreateGameObject(CAPSULE);
	}

	if (ImGui::MenuItem("Create Cylinder"))
	{
		//GameObjectManager::CreateGameObject(CYLINDER);
	}

	if (ImGui::MenuItem("Create Cube"))
	{
		//GameObjectManager::CreateGameObject(CUBE);
	}

	if (ImGui::MenuItem("Create Plane"))
	{
		//GameObjectManager::CreateGameObject(PLANE);
	}

	if (ImGui::MenuItem("Create Quad"))
	{
		//GameObjectManager::CreateGameObject(QUAD);
	}

	if (ImGui::MenuItem("Create Camera"))
	{
		//GameObjectManager::CreateGameObject(CAMERA);
	}

	if (ImGui::BeginMenu("Create Mesh"))
	{
		this->showMenuCreateMesh();
		ImGui::EndMenu();
	}

	//if (ImGui::MenuItem("Create Physics Cube"))
	//{
	//	GameObjectManager::CreateGameObject(PHYSICS_CUBE);
	//}
	//
	//if (ImGui::MenuItem("Create Physics Quad"))
	//{
	//	GameObjectManager::CreateGameObject(PHYSICS_QUAD);
	//}
	//
	//if (ImGui::MenuItem("Create Physics Objects"))
	//{
	//	GameObjectSpawner::SpawnPhysicsObjects();
	//}
}

void MenuScreen::showMenuWindow()
{
	if (ImGui::MenuItem("Inspector"))
	{
		//UIManager::SetEnabled(this->uiNames.INSPECTOR_SCREEN, true);
	}

	if (ImGui::MenuItem("Outliner"))
	{
		//UIManager::SetEnabled(this->uiNames.OUTLINER_SCREEN, true);
	}
	
	if (ImGui::MenuItem("Profiler"))
	{
		//UIManager::SetEnabled(this->uiNames.PROFILER_SCREEN, true);
	}
	
	if (ImGui::MenuItem("Console"))
	{
		//UIManager::SetEnabled(this->uiNames.CONSOLE_SCREEN, true);
	}

	if (ImGui::MenuItem("Color Picker"))
	{
		//UIManager::SetEnabled(this->uiNames.COLOR_PICKER_SCREEN, true);
	}

	ImGui::Separator();

	if (ImGui::BeginMenu("Themes"))
	{
		this->showMenuThemes();
		ImGui::EndMenu();
	}
}

void MenuScreen::showMenuAbout()
{
	if (ImGui::MenuItem("Credits"))
	{
		//UIManager::SetEnabled(this->uiNames.CREDITS_SCREEN, true);
	}
}

void MenuScreen::showMenuScreenCameras()
{

	//if (ImGui::MenuItem("Create Scene Camera"))
	//{
	//	SceneCameraHandler::AddSceneCamera();
	//}
	//if (ImGui::MenuItem("Scene Cameras Cycle Forward"))
	//{
	//	SceneCameraHandler::CycleGameCamerasForward();
	//}
	//if (ImGui::MenuItem("Scene Cameras Cycle Backward"))
	//{
	//	SceneCameraHandler::CycleGameCamerasBackward();
	//}
	//if (ImGui::MenuItem("Delete Last Scene Camera"))
	//{
	//	SceneCameraHandler::DeleteSceneCamera(SceneCameraHandler::GetSceneCameras().size()-1);
	//}

}

void MenuScreen::showFileDialogue()
{

	//ImGuiWindowFlags flags =
	//	ImGuiWindowFlags_AlwaysAutoResize;

	//if (ImGui::BeginPopupModal("Save Scene As:", (bool*)0, flags))
	//{
	//	const int size = 32;
	//	char fileName[size] = "NewSave.level";
	//	ImGui::InputText("File Name", fileName, size);

	//	if (ImGui::BeginTable("AcceptCancel", 3, ImGuiTableFlags_SizingStretchSame))
	//	{
	//		ImGui::TableNextColumn();
	//		if (ImGui::Button("Accept", ImVec2(ImGui::GetColumnWidth(0), 0)))
	//		{
	//			std::string name = fileName;
	//			std::cout << fileName[0] << "\n";
	//			std::cout << name << "\n";
	//			SaveSystem::GetInstance()->SaveScene(name);
	//			ImGui::CloseCurrentPopup();
	//		}

	//		ImGui::TableSetColumnIndex(2);
	//		if (ImGui::Button("Cancel", ImVec2(ImGui::GetColumnWidth(2), 0)))
	//		{
	//			ImGui::CloseCurrentPopup();
	//		}
	//		ImGui::EndTable();
	//	}

	//	ImGui::EndPopup();
	//}
}

void MenuScreen::showMenuOpenRecentScene()
{

	//for (const auto& entry : std::filesystem::directory_iterator("..\\Assets\\Scenes"))
	//{
	//	if (entry.is_regular_file())
	//	{
	//		std::wstring filename = entry.path().wstring();
	//		std::wstring displayName = std::filesystem::path(filename).filename().wstring();

	//		std::string name = std::string(displayName.begin(), displayName.end());
	//		if (ImGui::MenuItem(name.c_str()))
	//		{
	//			SaveSystem::GetInstance()->LoadScene(name);
	//		}
	//	}
	//}
}

void MenuScreen::showMenuThemes()
{
	if (ImGui::MenuItem("Dark"))
	{
		ImGui::StyleColorsDark();
	}

	if (ImGui::MenuItem("Light"))
	{
		ImGui::StyleColorsLight();
	}

	if (ImGui::MenuItem("Classic"))
	{
		ImGui::StyleColorsClassic();
	}

	if (ImGui::MenuItem("Crimson"))
	{
		this->styles.StyleColorsCrimson();
	}

	if (ImGui::MenuItem("Evangelion"))
	{
		this->styles.StyleColorsEvangelion();
	}
}

void MenuScreen::showMenuCreateMesh()
{

	//if (ImGui::MenuItem("Create teapot"))
	//{
	//	MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(MESH, true);
	//	mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj"));
	//	mesh->SetTexture(TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\brick.png"));
	//}
	//
	//if (ImGui::MenuItem("Create bunny"))
	//{
	//	MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(MESH, true);
	//	mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\bunny.obj"));
	//	mesh->SetTexture(TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\placeholder.jpg"));
	//}
	//
	//if (ImGui::MenuItem("Create armadillo"))
	//{
	//	MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(MESH, true);
	//	mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\armadillo.obj"));
	//	mesh->SetTexture(TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\placeholder.jpg"));
	//}

}
