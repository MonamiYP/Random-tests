#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light {
    private:
        glm::vec3 m_position;
        glm::vec3 m_color;

    public:
        Light() : m_position(glm::vec3(0.0f)), m_color(glm::vec3(1.0f)) {}
        Light(glm::vec3 position, glm::vec3 color) : m_position(position), m_color(color) {}
        ~Light() {}

        glm::vec3 GetPosition() const { return m_position; }
        glm::vec3 GetColor() const { return m_color; }
};