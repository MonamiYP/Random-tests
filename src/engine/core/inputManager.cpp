#include "InputManager.hpp"

#include <iostream>

void InputManager::processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    for (int key = 0; key < 350; key++) {
        m_keys[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }
}

void InputManager::mouseCallback(float xpos, float ypos) {
    if (m_firstMouse) {
        m_lastMousePos.x = xpos;
        m_lastMousePos.y = ypos;
        m_firstMouse = false;
    }

    m_mouseDelta.x = xpos - m_lastMousePos.x;
    m_mouseDelta.y = m_lastMousePos.y - ypos;

    m_lastMousePos.x = xpos;
    m_lastMousePos.y = ypos;
}

void InputManager::scrollCallback(float yscroll) {
    m_mouse_scroll = yscroll;
}

bool InputManager::toggleImGUI(GLFWwindow* window) {
    static bool g_pressed_prev = false;
    bool g_pressed = glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS;

    bool toggled = g_pressed && !g_pressed_prev;
    
    g_pressed_prev = g_pressed;
    return toggled;
}

bool InputManager::isKeyPressed(int key) {
    return key>=0 && key<350 ? m_keys[key] : false;
}