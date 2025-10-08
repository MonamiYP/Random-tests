#include "RenderSystem.hpp"

extern ECS ecs;

void RenderSystem::render(Shader* shader) {
    glCullFace(GL_BACK);
    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& modelComponent = ecs.GetComponent<ModelComponent>(entity);
        
        shader->Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
        model = glm::scale(model, transform.scale); 
        shader->SetMatrix4("u_model", model);
        modelComponent.model->Draw(*shader);
    }
}

void RenderSystem::clear() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}