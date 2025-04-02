#pragma once
#include <vector>
#include "Light.h"
class LightManager
{
public:
    typedef std::vector<Light*> Lights;
    static LightManager* getInstance();

    void addLight(Light* light);
    void deleteLight(Light* light);
    Lights& getLights();

private:
    LightManager() {}
    ~LightManager() {}
    LightManager(const LightManager&) {}
    LightManager& operator = (const LightManager&) {}
    static LightManager* sharedInstance;

    Lights lights;
};

