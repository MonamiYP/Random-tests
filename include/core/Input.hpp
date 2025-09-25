#pragma once

#include <GLFW/glfw3.h>
#include "EngineConfig.hpp"
#include "Camera.hpp"

class Input {
    private:
        Camera& m_camera;

        float m_lastX;
        float m_lastY;
        bool m_firstMouse;

    public:
        Input(Camera& camera) : m_camera(camera), m_firstMouse(true) {};
        void processInput(GLFWwindow* window, float deltaTime);
        void mouseCallback(float xPos, float yPos);
        void scrollCallback(float yscroll);

        bool toggleImGUI(GLFWwindow* window);
};