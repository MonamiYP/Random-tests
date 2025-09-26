#pragma once

#include <glm/glm.hpp>
#include <string>

struct Material {
    std::string shaderName;
    glm::vec3 color{1.0f};
};