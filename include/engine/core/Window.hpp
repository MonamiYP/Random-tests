#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "InputManager.hpp"

class Window {
    private:
        GLFWwindow* m_window = nullptr;

    public:
        bool setupWindow(float width, float height);
        void setupCallbacks(InputManager* input);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        GLFWwindow* getWindow() { return m_window; }
};