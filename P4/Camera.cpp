#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 center) {
    this->position = position;
    this->center = center;
    this->worldUp = glm::normalize(glm::vec3(0.f, 1.f, 0.f));

    this->distance = glm::distance(this->position, this->center);

    this->orientation = this->calcOrientation();
    this->view = this->calcView();
    this->projection = glm::mat4(1.0f);
}

void Camera::translate(glm::vec3 position) {
    this->position += position;
    this->center += position;
    this->orientation = this->calcOrientation();
    this->view = this->calcView();
}

void Camera::translate(float x, float y, float z) {
    this->translate(glm::vec3(x, y, z));
}

void Camera::move(float f, float r, float u) {
    if (f != 0.0f) {
        this->center += this->F * f;
        this->position += this->F * f;
    }

    if (r != 0.0f) {
        this->center += this->R * r;
        this->position += this->R * r;
    }
    
    if (u != 0.0f) {
        this->center += this->U * u;
        this->position += this->U * u;
    }

    this->orientation = this->calcOrientation();
    this->view = this->calcView();
}

void Camera::moveCenterWithPosition(glm::vec3 position) {
    this->position = position;
    this->center = glm::vec3(position + (this->F * this->distance));
    this->orientation = this->calcOrientation();
    this->view = this->calcView();
}

void Camera::movePositionWithCenter(glm::vec3 center) {
    this->center = center;
    this->position = glm::vec3(center - (this->F * this->distance));
    this->orientation = this->calcOrientation();
    this->view = this->calcView();
}

void Camera::swivel(float theta, glm::vec3 axis) {
    this->orientation = glm::rotate(this->orientation, theta, glm::normalize(axis));

    this->R.x = this->orientation[0][0];
    this->R.y = this->orientation[1][0];
    this->R.z = this->orientation[2][0];

    this->U.x = this->orientation[0][1];
    this->U.y = this->orientation[1][1];
    this->U.z = this->orientation[2][1];

    this->F.x = -this->orientation[0][2];
    this->F.y = -this->orientation[1][2];
    this->F.z = -this->orientation[2][2];

    this->center = glm::vec3(this->F + this->position);

    this->view = this->calcView();
}

void Camera::swivel(float theta, float x, float y, float z) {
    this->swivel(theta, glm::vec3(x, y, z));
}

void Camera::tilt(float theta, glm::vec3 axis) {
    if (axis.x) this->orientation = glm::rotate(this->orientation, theta, this->R);
    if (axis.y) this->orientation = glm::rotate(this->orientation, theta, this->U);
    if (axis.z) this->orientation = glm::rotate(this->orientation, theta, this->F);

    this->R.x = this->orientation[0][0];
    this->R.y = this->orientation[1][0];
    this->R.z = this->orientation[2][0];

    this->U.x = this->orientation[0][1];
    this->U.y = this->orientation[1][1];
    this->U.z = this->orientation[2][1];

    this->F.x = -this->orientation[0][2];
    this->F.y = -this->orientation[1][2];
    this->F.z = -this->orientation[2][2];

    this->center = glm::vec3(this->F + this->position);

    this->view = this->calcView();
}

void Camera::tilt(float theta, float x, float y, float z) {
    this->tilt(theta, glm::vec3(x, y, z));
}

void Camera::orbit(float theta, glm::vec3 axis) {
    glm::vec3 revF = glm::normalize(glm::vec3(this->position - this->center));
    glm::vec3 revR = glm::normalize(glm::cross(this->F, this->worldUp));
    glm::vec3 revU = glm::normalize(this->worldUp);

    glm::mat4 orientation = glm::mat4(1.0f);

    orientation[0][0] = revR.x;
    orientation[1][0] = revR.y;
    orientation[2][0] = revR.z;

    orientation[0][1] = revU.x;
    orientation[1][1] = revU.y;
    orientation[2][1] = revU.z;

    orientation[0][2] = -revF.x;
    orientation[1][2] = -revF.y;
    orientation[2][2] = -revF.z;

    if (axis.x) orientation = glm::rotate(orientation, theta, revR);
    if (axis.y) orientation = glm::rotate(orientation, theta, revU);
    if (axis.z) orientation = glm::rotate(orientation, theta, revF);

    revF.x = -orientation[0][2];
    revF.y = -orientation[1][2];
    revF.z = -orientation[2][2];

    this->position = glm::vec3((revF * this->distance) + this->center);
    this->orientation = this->calcOrientation();
    this->view = this->calcView();
}

void Camera::orbit(float theta, float x, float y, float z) {
    this->orbit(theta, glm::vec3(x, y, z));
}

glm::mat4 Camera::calcView() {
    glm::mat4 positionMat = glm::translate(glm::mat4(1.0f), this->position * -1.0f);
    return glm::mat4(this->orientation * positionMat);
}

glm::mat4 Camera::calcOrientation() {
    this->F = glm::normalize(glm::vec3(this->center - this->position));
    this->R = glm::normalize(glm::cross(F, this->worldUp));
    this->U = glm::normalize(glm::cross(R, F));

    glm::mat4 orientation = glm::mat4(1.0f);
    
    orientation[0][0] = this->R.x;
    orientation[1][0] = this->R.y;
    orientation[2][0] = this->R.z;

    orientation[0][1] = this->U.x;
    orientation[1][1] = this->U.y;
    orientation[2][1] = this->U.z;

    orientation[0][2] = -this->F.x;
    orientation[1][2] = -this->F.y;
    orientation[2][2] = -this->F.z;

    return orientation;
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
    this->orientation = this->calcOrientation();
    this->view = this->calcView();
}

glm::vec3 Camera::getCenter() {
    return this->center;
}

void Camera::setCenter(glm::vec3 center) {
    this->center = center;
    this->orientation = this->calcOrientation();
    this->view = this->calcView();
}

float Camera::getCenterDistance() {
    return this->distance;
}

glm::mat4 Camera::getView() {
    return this->view;
}

glm::mat4 Camera::getProjection() {
    return this->projection;
}