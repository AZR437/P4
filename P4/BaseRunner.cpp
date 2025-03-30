#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "Time.h"

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

    this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cao, Cordero, ShuTu", NULL, NULL);
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
}

BaseRunner::~BaseRunner()
{

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
}

void BaseRunner::render()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GameObjectManager::getInstance()->draw(this->window);
}
