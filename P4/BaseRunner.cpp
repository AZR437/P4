#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "Time.h"
#include "ShaderManager.h"

void keyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mod
)
{

}

void mouseButtonCallback(
    GLFWwindow* window,
    int button,
    int action,
    int mods
)
{

}

void cursorPosCallback(
    GLFWwindow* window,
    double xPos,
    double yPos
)
{

}

BaseRunner::BaseRunner()
{
    if (!glfwInit())
        exit(0);

    this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Scene Viewer", NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        exit(0);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(this->window);
    gladLoadGL();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_DEPTH_TEST);


    glfwSetKeyCallback(this->window, keyCallback);
    glfwSetCursorPosCallback(this->window, cursorPosCallback);
    glfwSetMouseButtonCallback(this->window, mouseButtonCallback);

    UIManager::initialize(this->window);

    ShaderManager::getInstance()->load("Default", "Shaders/Default.vert", "Shaders/Default.frag");
    ShaderManager::getInstance()->load("Skybox", "Shaders/Skybox.vert", "Shaders/Skybox.frag");
}

BaseRunner::~BaseRunner()
{
    UIManager::destroy();
}

void BaseRunner::run()
{
    while (!glfwWindowShouldClose(this->window))
    {
        Time::getInstance()->logFrameStart();
        this->processEvents();
        this->update();
        this->render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();

        Time::getInstance()->logFrameEnd();
    }

    glfwTerminate();
}

void BaseRunner::processEvents()
{

}

void BaseRunner::update()
{
    GameObjectManager::getInstance()->update();
    UIManager::getInstance()->newFrame();
}

void BaseRunner::render()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.1f, 0.0f, 0.005f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GameObjectManager::getInstance()->draw(this->window);
    UIManager::getInstance()->drawAllUI();
}
