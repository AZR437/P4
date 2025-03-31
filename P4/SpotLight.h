#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
    glm::vec3 direction;
    float cutOff;

public:
    SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff = 1.0f);

public:
    glm::vec3 getDirection();
    void setDirection(glm::vec3 direction);

    float getCutoff();
    void setCutOff(float cutOff);
};