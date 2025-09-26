#pragma once

#include <GLFW/glfw3.h>

class ImGUI {
    private:
        
    public:
        ImGUI();
        ~ImGUI();
        
        void setupImGUI(GLFWwindow* window);
        void drawGUI();
};