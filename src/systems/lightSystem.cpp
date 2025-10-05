#include "LightSystem.hpp"

extern ECS ecs;

void LightSystem::setupShaders() {
    addLightToShader(ResourceManager::getShader("default"));
    addLightToShader(ResourceManager::getShader("terrain"));
}

void LightSystem::addLightToShader(Shader* shader) {
    int index = 0;
    shader->Bind();

    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& light = ecs.GetComponent<Light>(entity);

        shader->SetFloat("u_pointLights["+std::to_string(index)+"].constant", light.constant);
        shader->SetFloat("u_pointLights["+std::to_string(index)+"].linear", light.linear);
        shader->SetFloat("u_pointLights["+std::to_string(index)+"].quadratic", light.quadratic);

        shader->SetVector3("u_pointLights["+std::to_string(index)+"].position", transform.position);
        shader->SetVector3("u_pointLights["+std::to_string(index)+"].ambient", light.ambient);
        shader->SetVector3("u_pointLights["+std::to_string(index)+"].diffuse", light.diffuse);
        shader->SetVector3("u_pointLights["+std::to_string(index)+"].specular", light.specular);
        index++;
    }

    shader->SetInt("u_pointLights_count", index);
}