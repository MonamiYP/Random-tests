#pragma once
#include <vector>
#include <glm/glm.hpp>

class Triangle {
    private:

    public:
        static std::vector<float> GetVertices() {
            return {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
            };
        }

        static std::vector<unsigned int> GetIndices() {
            return { 0, 1, 2 };
        }
};