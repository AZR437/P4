#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "ShaderManager.h"
#include "Time.h"
#include "Input.h"
#include "LightManager.h"
#include "DirLight.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "CameraController.h"
#include "MeshDisplay.h"
#include "CameraManager.h"

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

    Time::initialize();
    Input::initialize(this->window);
    UIManager::initialize(this->window);

    ShaderManager::getInstance()->load("Default", "Shaders/Default.vert", "Shaders/Default.frag");
    ShaderManager::getInstance()->load("Skybox", "Shaders/Skybox.vert", "Shaders/Skybox.frag");

    LightManager::getInstance()->addLight(new DirLight(glm::vec3(1.0f)));
    TextureManager::getInstance()->loadSkybox("NightSky", "Skybox");

    VFShaders* skyShaders = ShaderManager::getInstance()->getShaders("Skybox");
    GLuint* skyTex = TextureManager::getInstance()->getTexture("NightSky");
    std::cout << *skyTex << "\n";
    this->skybox = new Skybox(skyShaders, skyTex);
    
    //MeshManager::getInstance()->loadMeshDataAsync("Bunny", );

    CameraManager::getInstance()->getCamera()->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
    CameraController* controller = new CameraController();
    GameObjectManager::getInstance()->addObject(controller);

    MeshDisplay* meshDisplay = new MeshDisplay();
    GameObjectManager::getInstance()->addObject(meshDisplay);
}

BaseRunner::~BaseRunner()
{
    UIManager::destroy();
}

void BaseRunner::run()
{
    while (!glfwWindowShouldClose(this->window))
    {
        Time::logFrameStart();
        this->processEvents();
        this->update();
        this->render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();

        Time::logFrameEnd();
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
    //glClearColor(0.1f, 0.0f, 0.005f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->skybox->draw();
    GameObjectManager::getInstance()->draw();
    UIManager::getInstance()->drawAllUI();
}
