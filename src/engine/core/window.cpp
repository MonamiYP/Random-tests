#include "Window.hpp"

bool Window::setupWindow() {
    // setup GLFW
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    
    // setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    return true;
}

void Window::setupCallbacks(InputManager* input) {
    glfwSetWindowUserPointer(m_window, input);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
        InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
        if (input) input->mouseCallback((float)xpos, (float)ypos);
    });
    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xscroll, double yscroll) {
        InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
        if (input) input->scrollCallback((float)yscroll);
    });
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}