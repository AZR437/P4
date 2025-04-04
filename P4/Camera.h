#pragma once
#include <glm/glm.hpp>
class Camera
{
protected:
    glm::vec3 position;         // Camera Position
    glm::vec3 center;           // Camera Center (Point of Interest)
    glm::vec3 worldUp;          // World's orientation

    glm::vec3 F;                // Forward Direction
    glm::vec3 R;                // Right Direction
    glm::vec3 U;                // Up Direction

    glm::mat4 orientation;      // Camera Orientation
    glm::mat4 view;             // Camera View Matrix
    glm::mat4 projection;       // Camera Projection Matrix

    float distance;

public:
    Camera(glm::vec3 position, glm::vec3 center);

public:
    void translate(glm::vec3 position);
    void translate(float x, float y, float z);
    void move(float f, float r, float u);
    void moveCenterWithPosition(glm::vec3 position);
    void movePositionWithCenter(glm::vec3 center);
    void swivel(float theta, glm::vec3 axis);
    void swivel(float theta, float x, float y, float z);
    void tilt(float theta, glm::vec3 axis);
    void tilt(float theta, float x, float y, float z);
    void orbit(float theta, glm::vec3 axis);
    void orbit(float theta, float x, float y, float z);

protected:
    glm::mat4 calcOrientation();
    glm::mat4 calcView();
    virtual glm::mat4 calcProjection() = 0;

public:
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);

    glm::vec3 getCenter();
    void setCenter(glm::vec3 center);

    float getCenterDistance();

    glm::mat4 getView();

    glm::mat4 getProjection();
};
