#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Input.hpp"

class Window {
    private:
        const float WINDOW_WIDTH = 1200.0f;
        const float WINDOW_HEIGHT = 800.0f;
        GLFWwindow* m_window = nullptr;

    public:
        bool setupWindow();
        void setupCallbacks(Input* input);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        GLFWwindow* getWindow() { return m_window; }
};