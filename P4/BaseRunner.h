#pragma once

#include <unordered_map>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Skybox.h"

class BaseRunner
{
public:
    BaseRunner();
    ~BaseRunner();

    void run();

    const int TARGET_FPS = 120;
    const double FRAME_TIME = 1000.0 / TARGET_FPS;

    static const int WINDOW_WIDTH = 1024;
    static const int WINDOW_HEIGHT = 768;

private:
    void update();
    void render();

private:
    GLFWwindow* window;
    Skybox* skybox;
};

