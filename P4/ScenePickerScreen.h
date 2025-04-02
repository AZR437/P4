#pragma once
#include "AUIScreen.h"
class ScenePickerScreen : public AUIScreen
{
protected:
	ScenePickerScreen();
	~ScenePickerScreen();
	virtual void drawUI() override;

	friend class UIManager;

};

