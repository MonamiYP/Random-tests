#include "Input.hpp"

void Input::processInput(ApplicationState& state) {
    if (glfwGetKey(state.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(state.window, true);

    if (glfwGetKey(state.window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera->ProcessKeyboardInput(FORWARDS, state.deltaTime);
    if (glfwGetKey(state.window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera->ProcessKeyboardInput(BACKWARDS, state.deltaTime);
    if (glfwGetKey(state.window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->ProcessKeyboardInput(LEFT, state.deltaTime);
    if (glfwGetKey(state.window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->ProcessKeyboardInput(RIGHT, state.deltaTime);
    if (glfwGetKey(state.window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera->ProcessKeyboardInput(UP, state.deltaTime);
    if (glfwGetKey(state.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_camera->ProcessKeyboardInput(DOWN, state.deltaTime);

    toggleImGUI(state);
}

void Input::mouseCallback(float xpos, float ypos) {
    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    m_camera->ProcessMouseInput(xoffset, yoffset);
}

void Input::scrollCallback(float yscroll) {
    m_camera->ProcessScrollInput(yscroll);
}

void Input::toggleImGUI(ApplicationState& state) {
    static bool g_pressed_prev = false;
    bool g_pressed = glfwGetKey(state.window, GLFW_KEY_G) == GLFW_PRESS;

    if (g_pressed && !g_pressed_prev) {
        state.guiEnable = !state.guiEnable;
        if (state.guiEnable) {
            glfwSetInputMode(state.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(state.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    g_pressed_prev = g_pressed;
}