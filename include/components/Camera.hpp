#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera {
    glm::vec3 forward{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};
    glm::vec3 right{1.0f, 0.0f, 0.0f};
    glm::vec3 worldUp{0.0f, 1.0f, 0.0f};

    float fov{40.0f};
    float aspectRatio{1.0f};
    glm::vec2 clip{1.0f, 10.0f};

    float movementSpeed{3.0f};
    float mouseSensitivity{0.1f};

    glm::mat4 viewMatrix{1.0f};
    glm::mat4 projectionMatrix{1.0f};
};