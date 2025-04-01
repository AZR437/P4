#pragma once
#include <iostream>
#include "Camera.h"

class CameraManager
{
public:
    static CameraManager* getInstance();
    Camera* getCamera();

private:
    CameraManager();
    ~CameraManager();
    CameraManager(const CameraManager&) {}
    CameraManager& operator = (const CameraManager&) {}
    static CameraManager* sharedInstance;

    Camera* camera;
};

