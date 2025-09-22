#include "Window.hpp"

GLFWwindow* Window::setupWindow() {
    // setup GLFW
    if (!glfwInit()) return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    
    // setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glEnable(GL_DEPTH_TEST);
    return window;
}

void Window::setupCallbacks(GLFWwindow* window, Input* input) {
    glfwSetWindowUserPointer(window, input);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
        if (input) input->mouseCallback((float)xpos, (float)ypos);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xscroll, double yscroll) {
        Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
        if (input) input->scrollCallback((float)yscroll);
    });
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}