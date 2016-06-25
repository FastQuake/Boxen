#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "Camera.hpp"
using namespace std;

Camera::Camera() {
    speed = 0.002; // sensitivity, basically; maybe should be an input setting?
    position = glm::vec3(0, 0, 0);
    lookat = glm::vec3(0, 0, 0);

    right = glm::vec3(1, 0, 0);
    up = glm::vec3(0, 1, 0);

    pitch = M_PI;
    yaw = 0;
    updateLookat();
}

void Camera::move(float amount) {
    position += amount*lookat;
}

void Camera::strafe(float amount) {
    position += amount*right;
}

void Camera::turn(float pitch, float yaw) {
    this->rawTurn(speed*pitch, speed*yaw);
}

void Camera::rawTurn(float pitch, float yaw) {
    this->pitch += pitch;
    this->yaw += yaw;
    updateLookat();
}

void Camera::updateLookat() {
    lookat.x = cos(pitch) * cos(yaw);
    lookat.y = sin(pitch);
    lookat.z = cos(pitch) * sin(yaw);
    right = glm::cross(lookat, up);
}

glm::mat4 Camera::view() {
    return glm::lookAt(position, lookat+position, up);
}
