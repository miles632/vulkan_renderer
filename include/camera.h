#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
    glm::vec3 pos = {0.0f, 0.0f, 3.0f};
    glm::vec3 front = {0.0f, 0.0f, -1.0f};
    const glm::vec3 up = {0.0f, 1.0f, 0.0f};

    float yaw = -90.0f;
    float pitch = 0.0f;

    const float speed = 5.0f;

    bool keys[1024] = {false};

    void move(float dT);
    void mouse(float xOffset, float yOffset, float sensitivity = 0.1f);
    void updateFront();
    glm::mat4 getViewMatrix() const;
};
