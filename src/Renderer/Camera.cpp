#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "Camera.hpp"
using namespace std;

Camera::Camera() {
    position = glm::vec3(0, 0, 0);
    lookat = glm::vec3(0, 0, -1);

    right = glm::vec3(1, 0, 0);
    up = glm::vec3(0, 1, 0);

    pitch = 0;
    yaw = 0;
}

void Camera::move(float amount) {
    position += amount*lookat;
}

void Camera::strafe(float amount) {
    position += amount*right;
}

void Camera::turn(float pitch, float yaw) {
    this->pitch += pitch;
    this->yaw += yaw;

    lookat.x = cos(pitch) * cos(yaw);
    lookat.y = sin(pitch);
    lookat.z = cos(pitch) * sin(yaw);
}

glm::mat4 Camera::view() {
    return glm::lookAt(position, lookat+position, up);
}
