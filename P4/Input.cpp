#include "Input.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

Input* Input::sharedInstance = NULL;

void Input::keyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mod
)
{
    if (action == GLFW_PRESS)
    {
        sharedInstance->keyState[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        sharedInstance->keyState[key] = false;
    }
}

void Input::mouseButtonCallback(
    GLFWwindow* window,
    int button,
    int action,
    int mods
)
{

}

void Input::cursorPosCallback(
    GLFWwindow* window,
    double xPos,
    double yPos
)
{
    sharedInstance->cursorPos = glm::vec2(xPos, yPos);
}

void Input::initialize(GLFWwindow* window)
{
    sharedInstance = new Input(window);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Input::update()
{
    if (!sharedInstance->enabled ||
        ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) ||
        ImGui::IsAnyItemHovered()) return;

}

void Input::destroy()
{
    delete sharedInstance;
}

glm::vec2 Input::getCursorPosition()
{
    return sharedInstance->cursorPos;
}

void Input::setCursorPosition(const float& x, const float& y)
{
    glfwSetCursorPos(sharedInstance->window, x, y);
}

void Input::setCursorPosition(const glm::vec2& position)
{
    glfwSetCursorPos(sharedInstance->window, position.x, position.y);
}

void Input::showCursor(bool show)
{
    //::ShowCursor(show);
}

bool Input::isKey(int key)
{
    return sharedInstance->keyState[key];
}

bool Input::isKeyDown(int key)
{

    bool isKeyDown = false;
    //if ((this->keysState[key] & 0x80) &&
    //    this->keysState[key] != this->oldKeysState[key])
    //    isKeyDown = true;

    return isKeyDown;
}

bool Input::isKeyUp(int key)
{

    bool isKeyUp = false;
    //if (!(this->keysState[key] & 0x80) &&
    //    this->keysState[key] != this->oldKeysState[key])
    //    isKeyUp = true;

    return isKeyUp;
}

bool Input::getEnabled()
{
    return sharedInstance->enabled;
}

void Input::setEnabled(bool enabled)
{
    sharedInstance->enabled = enabled;
}

Input::Input(GLFWwindow* window)
{
    this->window = window;
    this->cursorPos = glm::vec2(0.0f);
}

Input::~Input()
{

}
