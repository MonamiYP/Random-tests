#include "TerrainSystem.hpp"

/* Note this only supports one planet for now, update if more planets required but fine for now */

extern ECS ecs;

void TerrainSystem::render(Shader* shader) {
    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& terrain = ecs.GetComponent<Terrain>(entity);

        shader->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
        shader->SetMatrix4("u_model", model);
        shader->SetFloat("u_radius", terrain.radius);

        shader->SetFloat("u_fractalNoiseAmplitude", terrain.fractal.amplitude);
        shader->SetFloat("u_fractalNoiseLacunarity", terrain.fractal.lacunarity);
        shader->SetFloat("u_fractalNoisePersistence", terrain.fractal.persistence);
        shader->SetFloat("u_fractalNoiseFrequency", terrain.fractal.frequency);

        shader->SetFloat("u_ridgeNoiseAmplitude", terrain.ridge.amplitude);
        shader->SetFloat("u_ridgeNoiseLacunarity", terrain.ridge.lacunarity);
        shader->SetFloat("u_ridgeNoisePersistence", terrain.ridge.persistence);
        shader->SetFloat("u_ridgeNoiseFrequency", terrain.ridge.frequency);

        shader->SetFloat("u_floorDepth", terrain.floorDepth);
        
        m_VAO.Bind();

        glPatchParameteri(GL_PATCH_VERTICES, 4);
        glDrawArrays(GL_PATCHES, 0, 4*terrain.resolution*terrain.resolution*6);
        m_VAO.Unbind();
    }
}

void TerrainSystem::updateGUI() {
    for (const auto& entity : m_Entities) {
        auto& terrain = ecs.GetComponent<Terrain>(entity);

        ImGui::Begin("Terrain Controls");
        if (ImGui::TreeNode("Fractal Noise")) {
            ImGui::SliderFloat("Frequency", &terrain.fractal.frequency, 0.0f, 0.5f, "%.3f");
            ImGui::SliderFloat("Lacunarity", &terrain.fractal.lacunarity, 1.0f, 4.0f, "%.3f");
            ImGui::SliderFloat("Persistence", &terrain.fractal.persistence, 0.0f, 1.0f, "%.3f");
            ImGui::SliderFloat("Amplitude", &terrain.fractal.amplitude, 0.0f, 0.05f, "%.3f");
            
            ImGui::TreePop();
        }   
        if (ImGui::TreeNode("Ridge Noise")) {
            ImGui::SliderFloat("Frequency", &terrain.ridge.frequency, 0.0f, 10.0f, "%.1f");
            ImGui::SliderFloat("Lacunarity", &terrain.ridge.lacunarity, 1.0f, 4.0f, "%.3f");
            ImGui::SliderFloat("Persistence", &terrain.ridge.persistence, 0.0f, 1.0f, "%.3f");
            ImGui::SliderFloat("Amplitude", &terrain.ridge.amplitude, 0.0f, 0.05f, "%.3f");

            ImGui::TreePop();
        }
        ImGui::SliderFloat("Floor depth", &terrain.floorDepth, 0.0f, 0.005f, "%.4f");
        ImGui::End();
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