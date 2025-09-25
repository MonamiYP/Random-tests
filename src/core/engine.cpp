#include "Engine.hpp"

void Engine::Run() {
    Init();

    while (!glfwWindowShouldClose(m_window.getWindow())) {
        float currentTime = glfwGetTime();
        m_config.deltaTime = currentTime - m_config.lastTime;
        m_config.lastTime = currentTime;

        Update();
        ProcessInput();
        Render();

        glfwSwapBuffers(m_window.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
}

void Engine::Init() {
    m_ecs.Init();
    if (!m_window.setupWindow()) throw std::runtime_error("Failed to create window");

    m_window.setupCallbacks(&m_input);

    m_imGUI.setupImGUI(m_window.getWindow());

    std::string vertex_source = m_shader.ParseShader("../res/shaders/basic.vertex");
    std::string fragment_source = m_shader.ParseShader("../res/shaders/basic.fragment");
    m_shader.CreateShaderProgram(vertex_source, fragment_source);

    m_light = Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.8f, 0.8f));
    m_shader.SetLight(m_light);

    m_carModel.LoadModel("../res/assets/car/car.obj");
}

void Engine::Update() {
    if (m_input.toggleImGUI(m_window.getWindow())) {
        m_config.guiEnable = !m_config.guiEnable;
        if (m_config.guiEnable) {
             glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
             glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }  
    }

    m_shader.Bind();
    m_shader.SetMatrix4("u_view", m_camera.GetCameraView());
    m_shader.SetMatrix4("u_projection", m_camera.GetCameraProjection());
    m_shader.SetVector3("u_viewPos", m_camera.GetPosition());
}

void Engine::ProcessInput() {
    m_input.processInput(m_window.getWindow(), m_config.deltaTime);
}

void Engine::Render() {
    m_renderer.Clear();

    if(m_config.guiEnable) { m_imGUI.drawGUI(); };

    m_carModel.Draw(m_shader);
}