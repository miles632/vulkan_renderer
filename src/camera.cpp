#include "camera.h"

void Camera::move(float dT) {
    if (keys[GLFW_KEY_W])
        pos += speed * front * dT;
    if (keys[GLFW_KEY_S])
        pos -= speed * front * dT;
    if (keys[GLFW_KEY_A])
        pos -= glm::normalize(glm::cross(front, up)) * speed * dT;
    if (keys[GLFW_KEY_D])
        pos += glm::normalize(glm::cross(front, up)) * speed * dT;
}

void Camera::updateFront() {

}

glm::mat4 Camera::getViewMatrix() const {

}

void Camera::mouse(float xOffset, float yOffset, float sensitivity) {

}



