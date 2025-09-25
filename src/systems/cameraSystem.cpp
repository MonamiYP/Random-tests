#include "CameraSystem.hpp"

extern ECS ecs;

void CameraSystem::Update(float deltaTime) {
    InputManager& input = InputManager::Get();

    ProcessKeyboardInput(input, deltaTime);
    ProcessMouseInput(input, deltaTime);
}

void CameraSystem::ProcessKeyboardInput(InputManager& input, float deltaTime) {
    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& camera = ecs.GetComponent<Camera>(entity);

        float cameraSpeed = camera.movementSpeed * deltaTime;

        if (input.isKeyPressed(GLFW_KEY_SPACE))
            transform.position += cameraSpeed * camera.up;
        if (input.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
            transform.position -= cameraSpeed * camera.up;
        
        if (input.isKeyPressed(GLFW_KEY_W))
            transform.position += cameraSpeed * camera.forward;
        if (input.isKeyPressed(GLFW_KEY_S))
            transform.position -= cameraSpeed * camera.forward;
        if (input.isKeyPressed(GLFW_KEY_A))
            transform.position -= cameraSpeed * glm::normalize(glm::cross(camera.forward, camera.up));
        if (input.isKeyPressed(GLFW_KEY_D))
            transform.position += cameraSpeed * glm::normalize(glm::cross(camera.forward, camera.up));
    }
}

void CameraSystem::ProcessMouseInput(InputManager& input, float deltaTime) {
    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& camera = ecs.GetComponent<Camera>(entity);

        transform.rotation.x += camera.mouseSensitivity * input.getMouseDelta().x;
        transform.rotation.y += camera.mouseSensitivity * input.getMouseDelta().y;

        if (transform.rotation.y > 89.0f) { transform.rotation.y = 89.0f; }
        if (transform.rotation.y < -89.0f) { transform.rotation.y = -89.0f; }

    }
    UpdateVectors();
}

void CameraSystem::UpdateVectors() {
    for (const auto& entity : m_Entities) {
        auto& transform = ecs.GetComponent<Transform>(entity);
        auto& camera = ecs.GetComponent<Camera>(entity);
        
        glm::vec3 frontDir;
        frontDir.x = cos(glm::radians(transform.rotation.x)) * cos(glm::radians(transform.rotation.y));
        frontDir.y = sin(glm::radians(transform.rotation.y));
        frontDir.z = sin(glm::radians(transform.rotation.x)) * cos(glm::radians(transform.rotation.y));
        
        camera.forward = glm::normalize(frontDir);
        camera.right = glm::normalize(glm::cross(camera.forward, camera.worldUp));
        camera.up  = glm::normalize(glm::cross(camera.right, camera.forward));

        camera.viewMatrix = glm::lookAt(transform.position, transform.position + camera.forward, camera.up);
        camera.projectionMatrix = glm::perspective(camera.fov, camera.aspectRatio, camera.clip.x, camera.clip.y);
    }
}