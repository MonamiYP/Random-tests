#pragma once

#include <GLFW/glfw3.h>
#include "EngineConfig.hpp"
#include "Camera.hpp"

class InputManager {
    private:
        bool m_firstMouse = true;

        bool m_keys[350]{ false };
        bool m_mouseButtons[8]{ false };

        glm::vec2 m_lastMousePos{ 0.0f, 0.0f };
        glm::vec2 m_mouseDelta{ 0.0f, 0.0f };
        float m_mouse_scroll;

    public:
        InputManager() {};
        
        // Singleton access
        static InputManager& Get() {
            static InputManager instance;
            return instance;
        }

        void processInput(GLFWwindow* window, float deltaTime);
        void mouseCallback(float xPos, float yPos);
        void scrollCallback(float yscroll);

        bool toggleImGUI(GLFWwindow* window);
        
        bool isKeyPressed(int key);
        glm::vec2 getMouseDelta() { return m_mouseDelta; }

        void resetMouse() { m_mouseDelta = glm::vec2(0.0f, 0.0f); }
};