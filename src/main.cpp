#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "Renderer.hpp"
#include "ImGUI.hpp"
#include "ApplicationState.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "Camera.hpp"

#include "primitives/Rectangle.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

int main() {
    ApplicationState state;
    Window window;
    Renderer renderer;

    state.window = window.setupWindow();
    if (!state.window) return -1;
    
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Input input(&camera);
    window.setupCallbacks(state.window, &input);
    ImGUI imGUI(state.window);

    std::vector<float> vertices = Rectangle::GetVertices();
    std::vector<unsigned int> indices = Rectangle::GetIndices();

    VertexArray vao;
    VertexBuffer vbo(vertices.data(), vertices.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.AddAttribute(GL_FLOAT, 3);
    IndexBuffer ibo(indices.data(), indices.size() * sizeof(unsigned int));
    vao.AddBuffer(vbo, layout);

    Shader shader;
    std::string vertex_source = shader.ParseShader("../res/shaders/basic.vertex");
    std::string fragment_source = shader.ParseShader("../res/shaders/basic.fragment");
    shader.CreateShaderProgram(vertex_source, fragment_source);

    while (!glfwWindowShouldClose(state.window)) {
        float currentTime = glfwGetTime();
        state.deltaTime = currentTime - state.lastTime;
        state.lastTime = currentTime;

        shader.Bind();
        shader.SetMatrix4("u_view", camera.GetCameraView());
        shader.SetMatrix4("u_projection", camera.GetCameraProjection());

        input.processInput(state);
        renderer.Clear();

        if(state.guiEnable) { imGUI.drawGUI(); };

        renderer.Draw(vao, ibo, shader);

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}