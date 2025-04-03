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
	std::shared_ptr<SceneClient> client;

};

