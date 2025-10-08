#pragma once

#include <glm/glm.hpp>

enum class LightCasterType {
    Directional = 0,
    Point = 1,
    Spot = 2
};

struct Light {
    LightCasterType type = LightCasterType::Point;

    glm::vec3 ambient = glm::vec3(1.0f);
    glm::vec3 diffuse = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(1.0f);

    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);

    bool castsShadow = false;
    glm::mat4 lightSpaceMatrix;
};