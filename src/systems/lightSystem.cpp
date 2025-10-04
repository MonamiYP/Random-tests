#include "LightSystem.hpp"

extern ECS ecs;

void LightSystem::setupShaderLights() {
    int index = 0;
    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& light = ecs.GetComponent<Light>(entity);

        Shader* shader = ResourceManager::getShader("terrain");

        shader->SetFloat("pointLights["+std::to_string(index)+"].constant",  light.constant);
        shader->SetFloat("pointLights["+std::to_string(index)+"].linear",    light.linear);
        shader->SetFloat("pointLights["+std::to_string(index)+"].quadratic", light.quadratic);

        shader->SetVector3("pointLights["+std::to_string(index)+"].position", transform.position);
        shader->SetVector3("pointLights["+std::to_string(index)+"].ambient", light.ambient);
        shader->SetVector3("pointLights["+std::to_string(index)+"].diffuse", light.diffuse);
        shader->SetVector3("pointLights["+std::to_string(index)+"].specular", light.specular);
        index++;
    }
}