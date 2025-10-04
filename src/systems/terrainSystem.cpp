#include "TerrainSystem.hpp"

/* Note this only supports one planet for now, update if more planets required but fine for now */

extern ECS ecs;

void TerrainSystem::render() {
    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& terrain = ecs.GetComponent<Terrain>(entity);

        Shader* shader = ResourceManager::getShader(terrain.shaderName);
        if (!shader) continue;

        shader->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
        shader->SetMatrix4("u_model", model);
        shader->SetFloat("u_radius", terrain.radius);

        
        ImGui::Begin("Terrain Controls");
        if (ImGui::TreeNode("Fractal Noise")) {
            ImGui::SliderFloat("Lacunarity", &terrain.lacunarity, 1.0f, 4.0f, "%.2f");
            ImGui::SliderFloat("Persistence", &terrain.persistence, 0.1f, 1.0f, "%.2f");
            ImGui::SliderFloat("Amplitude", &terrain.amplitude, 0.0f, 0.05f, "%.3f");
            ImGui::TreePop();
        }
        ImGui::End();


        shader->SetFloat("u_fractalNoiseAmplitude", terrain.amplitude);
        shader->SetFloat("u_fractalNoiseLacunarity", terrain.lacunarity);
        shader->SetFloat("u_fractalNoisePersistence", terrain.persistence);
        
        m_VAO.Bind();

        glPatchParameteri(GL_PATCH_VERTICES, 4);
        glDrawArrays(GL_PATCHES, 0, 4*terrain.resolution*terrain.resolution*6);
        m_VAO.Unbind();
    }
}

void TerrainSystem::generateVertices() {
    for (const auto& entity : m_Entities) {
        auto& terrain = ecs.GetComponent<Terrain>(entity);
        std::vector<float> vertices =getPatchedCubeVertices(terrain.radius, terrain.resolution);
        VertexBuffer VBO(&vertices[0], vertices.size() * sizeof(GLfloat));
        VertexBufferLayout layout;
        layout.AddAttribute(GL_FLOAT, 3);
        m_VAO.AddBuffer(VBO, layout);
        m_VAO.Unbind();
    }
    
}

std::vector<float> TerrainSystem::getPatchedCubeVertices(float radius, float resolution) {
    std::vector<float> vertices;
    float segment_width = radius*2/resolution;
    for (unsigned int j = 0; j < resolution; j++) {
        // Face 1
        for (unsigned int i = 0; i < resolution; i++) {
            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);
            vertices.push_back(-radius);

            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(j * segment_width - radius);
            vertices.push_back(-radius);
            
            vertices.push_back(i * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);
            vertices.push_back(-radius);

            vertices.push_back(i * segment_width - radius);
            vertices.push_back(j * segment_width - radius);
            vertices.push_back(-radius);
        }
    }
    // Face 2
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            vertices.push_back(i * segment_width - radius);
            vertices.push_back(j * segment_width - radius);
            vertices.push_back(radius);

            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(j * segment_width - radius);
            vertices.push_back(radius);

            vertices.push_back(i * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);
            vertices.push_back(radius);

            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);
            vertices.push_back(radius);
        }
    }
    // Face 3
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            vertices.push_back(radius);
            vertices.push_back(i * segment_width - radius);
            vertices.push_back(j * segment_width - radius);

            vertices.push_back(radius);
            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(j * segment_width - radius);

            vertices.push_back(radius);
            vertices.push_back(i * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);

            vertices.push_back(radius);
            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);
        }
    }
    // Face 4
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            vertices.push_back(-radius);
            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);

            vertices.push_back(-radius);
            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(j * segment_width - radius);

            vertices.push_back(-radius);
            vertices.push_back(i * segment_width - radius);
            vertices.push_back((j+1) * segment_width - radius);

            vertices.push_back(-radius);
            vertices.push_back(i * segment_width - radius);
            vertices.push_back(j * segment_width - radius);
        }
    }
    // Face 5
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            vertices.push_back(i * segment_width - radius);
            vertices.push_back(-radius);
            vertices.push_back(j * segment_width - radius);

            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(-radius);
            vertices.push_back(j * segment_width - radius);

            vertices.push_back(i * segment_width - radius);
            vertices.push_back(-radius);
            vertices.push_back((j+1) * segment_width - radius);

            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(-radius);
            vertices.push_back((j+1) * segment_width - radius);
        }
    }
    // Face 6
    for (unsigned int j = 0; j < resolution; j++) {
        for (unsigned int i = 0; i < resolution; i++) {
            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(radius);
            vertices.push_back((j+1) * segment_width - radius);

            vertices.push_back((i+1) * segment_width - radius);
            vertices.push_back(radius);
            vertices.push_back(j * segment_width - radius);

            vertices.push_back(i * segment_width - radius);
            vertices.push_back(radius);
            vertices.push_back((j+1) * segment_width - radius);
            
            vertices.push_back(i * segment_width - radius);
            vertices.push_back(radius);
            vertices.push_back(j * segment_width - radius);
        }
    }

    return vertices;
}