#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
    float constant;
    float linear;
    float quadratic;

public:
    PointLight(glm::vec3 position);

public:
    float getConstant();
    void setConstant(float constant);

    float getLinear();
    void setLinear(float linear);

    float getQuadratic();
    void setQuadratic(float quadratic);
};