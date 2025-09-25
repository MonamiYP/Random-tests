#include "Engine.hpp"

extern ECS ecs;

void Engine::Run() {
    Init();

    while (!glfwWindowShouldClose(m_window.getWindow())) {
        float currentTime = glfwGetTime();
        m_config.deltaTime = currentTime - m_config.lastTime;
        m_config.lastTime = currentTime;

        ProcessInput();
        Update();
        Render();

        glfwSwapBuffers(m_window.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
}

void Engine::Init() {
    ecs.Init();
    if (!m_window.setupWindow()) throw std::runtime_error("Failed to create window");

    m_window.setupCallbacks(&InputManager::Get());

    m_imGUI.setupImGUI(m_window.getWindow());

    std::string vertex_source = m_shader.ParseShader("../res/shaders/basic.vertex");
    std::string fragment_source = m_shader.ParseShader("../res/shaders/basic.fragment");
    m_shader.CreateShaderProgram(vertex_source, fragment_source);

    m_light = Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.8f, 0.8f));
    m_shader.SetLight(m_light);

    m_carModel.LoadModel("../res/assets/car/car.obj");

    RegisterComponents();
    RegisterSystems();

    m_camera = ecs.CreateEntity();
    ecs.AddComponent(m_camera, Camera {});
    ecs.AddComponent(m_camera, Transform {});
}

void Engine::Update() {
    if (InputManager::Get().toggleImGUI(m_window.getWindow())) {
        m_config.guiEnable = !m_config.guiEnable;
        if (m_config.guiEnable) {
             glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
             glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }  
    }

    m_cameraSystem->Update(m_config.deltaTime);
    auto& camera_camera = ecs.GetComponent<Camera>(m_camera);
    auto& camera_transform = ecs.GetComponent<Transform>(m_camera);

    m_shader.Bind();
    m_shader.SetMatrix4("u_view", camera_camera.viewMatrix);
    m_shader.SetMatrix4("u_projection", camera_camera.projectionMatrix);
    m_shader.SetVector3("u_viewPos", camera_transform.position);

    InputManager::Get().resetMouse();
}

void Engine::ProcessInput() {
    InputManager::Get().processInput(m_window.getWindow(), m_config.deltaTime);
}

void Engine::Render() {
    m_renderer.Clear();

    if(m_config.guiEnable) { m_imGUI.drawGUI(); };

    m_carModel.Draw(m_shader);
}

void Engine::RegisterComponents() {
    ecs.RegisterComponent<Transform>();
    ecs.RegisterComponent<Camera>();
}

void Engine::RegisterSystems() {
    m_cameraSystem = ecs.RegisterSystem<CameraSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<Transform>());
        signature.set(ecs.GetComponentType<Camera>());
        ecs.SetSystemSignature<CameraSystem>(signature);
    }
}