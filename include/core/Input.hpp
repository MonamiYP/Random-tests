#pragma once

#include <GLFW/glfw3.h>
#include "ApplicationState.hpp"
#include "Camera.hpp"

class Input {
    private:
        Camera* m_camera;
        static Input* s_instance;

        float m_lastX;
        float m_lastY;
        bool m_firstMouse;

    public:
        Input(Camera* camera) : m_camera(camera), m_firstMouse(true) {};
        void processInput(ApplicationState& state);
        void mouseCallback(float xPos, float yPos);
        void scrollCallback(float yscroll);

        void toggleImGUI(ApplicationState& state);
};