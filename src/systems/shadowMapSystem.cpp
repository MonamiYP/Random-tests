#include "ShadowMapSystem.hpp"

extern ECS ecs;

void ShadowMapSystem::render() {
//     for (const auto& entity : m_Entities) {
//         auto& transform = ecs.GetComponent<Transform>(entity);
//         auto& modelComponent = ecs.GetComponent<ModelComponent>(entity);
//         // auto& material = ecs.GetComponent<Material>(entity);
// ;
//         glm::mat4 modelMat = transform.getMatrix();


//         glm::mat4 lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 1.0f, 300.0f);
//             glm::mat4 lightView = glm::lookAt(-light.direction * 100.0f, glm::vec3(0.0f), glm::vec3(0, 1, 0));
//             m_lightSpaceMatrix = lightProjection * lightView;
            
//             Shader* shader_shadowMap = ResourceManager::getShader("shadowMap");
//             shader_shadowMap->Bind();
//             shader_shadowMap->SetMatrix4("u_lightSpaceMatrix", m_lightSpaceMatrix);

//             shadowMap.bindFrameBuffer(shadowMap.getFBO());
//             glBindFramebuffer(GL_FRAMEBUFFER, 0);

//         depthShader->SetMatrix4("u_model", modelMat);
//         model.model->Draw(*depthShader);
//     }
}