#include "LightSystem.hpp"

extern ECS ecs;

void LightSystem::setupShaders() {
    addLightToShader(ResourceManager::getShader("default"));
    addLightToShader(ResourceManager::getShader("terrain"));
}

void LightSystem::addLightToShader(Shader* shader) {
    int pointLightIndex = 0;
    int dirLightIndex = 0;
    shader->Bind();

    for (const auto& entity : m_Entities) {
        auto& light = ecs.GetComponent<Light>(entity);

        if (light.type == LightCasterType::Point) {
            auto& transform = ecs.GetComponent<Transform>(entity);
            shader->SetVector3("u_pointLights["+std::to_string(pointLightIndex)+"].position", transform.position);
            shader->SetVector3("u_pointLights["+std::to_string(pointLightIndex)+"].ambient", light.ambient);
            shader->SetVector3("u_pointLights["+std::to_string(pointLightIndex)+"].diffuse", light.diffuse);
            shader->SetVector3("u_pointLights["+std::to_string(pointLightIndex)+"].specular", light.specular);
            pointLightIndex++;
        } else if (light.type == LightCasterType::Directional) {
            shader->SetVector3("u_directionalLights["+std::to_string(dirLightIndex)+"].direction", light.direction);
            shader->SetVector3("u_directionalLights["+std::to_string(dirLightIndex)+"].ambient", light.ambient);
            shader->SetVector3("u_directionalLights["+std::to_string(dirLightIndex)+"].diffuse", light.diffuse);
            shader->SetVector3("u_directionalLights["+std::to_string(dirLightIndex)+"].specular", light.specular);
            dirLightIndex++;
        }
    }

    shader->SetInt("u_pointLights_count", pointLightIndex);
    shader->SetInt("u_directionalLights_count", dirLightIndex);
}