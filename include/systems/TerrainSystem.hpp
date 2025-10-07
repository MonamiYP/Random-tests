#pragma once

#include "ECS.hpp"
#include "Terrain.hpp"
#include "Transform.hpp"
#include "Shader.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class TerrainSystem : public System {
    private:
        VertexArray m_VAO;

        std::vector<float> getPatchedCubeVertices(float width, float resolution);
    public:
        void generateVertices();
        void render(Shader* shader);
        void updateGUI();
};