#pragma once
#include "AUIScreen.h"
#include "SceneClient.h"
class ScenePickerScreen : public AUIScreen
{
protected:
	ScenePickerScreen(std::shared_ptr<SceneClient> client);
	~ScenePickerScreen();
	virtual void drawUI() override;

	friend class UIManager;

private:
	void loadScene(unsigned int index);
	bool hasScene(unsigned int index);
	void toggleScene(unsigned int index);
	void destroyScene(unsigned int index);

	std::shared_ptr<SceneClient> client;
	bool sceneToggle[6] { false, false, false, false, false, false };
	float progress[5] { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
};

