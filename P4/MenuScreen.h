#pragma once
#include "AUIScreen.h"
#include "UINames.h"
#include "CustomStyles.h"

class MenuScreen : public AUIScreen
{
protected:
	MenuScreen();
	~MenuScreen();
	virtual void drawUI() override;

	friend class UIManager;

private:
	void showMenuFile();
	void showMenuGameObject();
	void showMenuWindow();
	void showMenuAbout();
	void showMenuScreenCameras();

	void showFileDialogue();
	void showMenuOpenRecentScene();
	void showMenuThemes();
	void showMenuCreateMesh();

	UINames uiNames;
	CustomStyles styles;

	bool openFileDialogue = false;
};

