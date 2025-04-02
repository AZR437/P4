#pragma once
#include <iostream>
#include <unordered_set>
#include <bitset>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Input
{
public:
	static void initialize(GLFWwindow* window);
	static void destroy();
	static void update();

	static glm::vec2 getCursorPosition();
	static void setCursorPosition(const float& x, const float& y);
	static void setCursorPosition(const glm::vec2& position);
	static void showCursor(bool show);

	static bool isMouseButton(int button);
	static bool isMouseButtonDown(int button);
	static bool isMouseButtonUp(int button);

	static bool isKey(int key);
	static bool isKeyDown(int key);
	static bool isKeyUp(int key);

	static bool getEnabled();
	static void setEnabled(bool enabled);

private:
	static void keyCallback(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mod
	);

	static void mouseButtonCallback(
		GLFWwindow* window,
		int button,
		int action,
		int mods
	);

	static void cursorPosCallback(
		GLFWwindow* window,
		double xPos,
		double yPos
	);

private:
	Input(GLFWwindow* window);
	~Input();
	Input(Input const&) {};
	Input& operator=(Input const&) {};
	static Input* sharedInstance;

	GLFWwindow* window;

	std::bitset<GLFW_KEY_LAST> keyState;
	std::bitset<GLFW_KEY_LAST> oldKeyState;
	std::bitset<GLFW_MOUSE_BUTTON_LAST> mouseState;
	std::bitset<GLFW_MOUSE_BUTTON_LAST> oldMouseState;
	glm::vec2 cursorPos;
	bool enabled = true;
};
