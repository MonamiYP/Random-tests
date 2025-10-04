#pragma once
#include <vector>
#include <glm/glm.hpp>

class Rectangle {
    private:

    public:
        static std::vector<float> GetVertices() {
            return {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left 
            };
        }

        static std::vector<unsigned int> GetIndices() {
            return {
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
            };
        }
};