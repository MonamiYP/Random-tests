#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
    Some note on coordinate systems:    
    - view matrix: transforms the world coordinates to view-space coordinates in such a way that each coordinate is as seen from the camera's point of view. 
    - projection matrix: project view-space coordinates to clip coordinates (-1.0 and 1.0 range, determine which vertices will end up on the screen). Projection to clip-space coordinates can add perspective if using perspective projection. 
*/

enum CameraMovementDir {
    UP, DOWN, LEFT, RIGHT, FORWARDS, BACKWARDS
};

class Camera {
    private:
        glm::vec3 m_position;
        glm::vec3 m_forwards;
        glm::vec3 m_up;

        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        float m_yaw;
        float m_pitch;

        float m_movementSpeed;
        float m_mouseSensitivity;

        float m_fov;
        float m_aspectRatio;
        float m_near;
        float m_far;

        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;

    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float aspect_ratio = 1.0f);
        ~Camera() {}

        glm::vec3 GetPosition() { return m_position; };
        glm::vec3 GetForwards() { return m_forwards; };

        glm::mat4 GetCameraView() { return glm::lookAt(m_position, m_position + m_forwards, m_up); };
        glm::mat4 GetCameraProjection() { return glm::perspective(m_fov, m_aspectRatio, m_near, m_far); };

        void ProcessKeyboardInput(CameraMovementDir dir, float deltaTime);
        void ProcessMouseInput(float xOffset, float yOffset);
        void ProcessScrollInput(float yScroll);
        void UpdateVectors();
};