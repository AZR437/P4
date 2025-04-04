#include "ProfilerScreen.h"
#include "CameraManager.h"
#include "Time.h"

ProfilerScreen::ProfilerScreen() : AUIScreen("PROFILER_SCREEN")
{
	
}

ProfilerScreen::~ProfilerScreen()
{

}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Profiler", NULL, ImGuiWindowFlags_NoResize);

	this->ticks += Time::getUnscaledDeltaTime();
	if (this->ticks > 1.0)
	{
		this->ticks = 0.0;
		this->fps = 1 / Time::getUnscaledDeltaTime();
	}

	std::string fpsCounter = "FPS: " + std::to_string(this->fps);
	ImGui::Text(fpsCounter.c_str());

	glm::vec3 camPos = CameraManager::getInstance()->getCamera()->getPosition();
	std::string posString = "(" + std::to_string(camPos.x) + ", " + std::to_string(camPos.y) + ", " + std::to_string(camPos.z) + ")";
	std::string camPosText = "Camera Position: " + posString;
	ImGui::Text(camPosText.c_str());

	ImGui::End();
}
