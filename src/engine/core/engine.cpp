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

    ResourceManager::loadShader("default", "../res/shaders/basic.vertex", "../res/shaders/basic.fragment");

    m_light = Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.8f, 0.8f));
    Shader* shader = ResourceManager::getShader("default");
    shader->Bind();
    shader->SetLight(m_light);

    RegisterComponents();
    RegisterSystems();
    CreateEntities();
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

    Shader* shader = ResourceManager::getShader("default");

    shader->Bind();
    shader->SetMatrix4("u_view", camera_camera.viewMatrix);
    shader->SetMatrix4("u_projection", camera_camera.projectionMatrix);
    shader->SetVector3("u_viewPos", camera_transform.position);

    InputManager::Get().resetMouse();
}

void Engine::ProcessInput() {
    InputManager::Get().processInput(m_window.getWindow(), m_config.deltaTime);
}

void Engine::Render() {
    m_renderSystem->clear();

    if(m_config.guiEnable) { m_imGUI.drawGUI(); };

    m_renderSystem->render();
}

void Engine::RegisterComponents() {
    ecs.RegisterComponent<Transform>();
    ecs.RegisterComponent<Camera>();
    ecs.RegisterComponent<ModelComponent>();
    ecs.RegisterComponent<Material>();
}

void Engine::RegisterSystems() {
    m_cameraSystem = ecs.RegisterSystem<CameraSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<Transform>());
        signature.set(ecs.GetComponentType<Camera>());
        ecs.SetSystemSignature<CameraSystem>(signature);
    }

    m_renderSystem = ecs.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<Transform>());
        signature.set(ecs.GetComponentType<ModelComponent>());
        signature.set(ecs.GetComponentType<Material>());
        ecs.SetSystemSignature<RenderSystem>(signature);
    }
}

void Engine::CreateEntities() {
    /* Camera */
    m_camera = ecs.CreateEntity();
    ecs.AddComponent(m_camera, Camera {});
    ecs.AddComponent(m_camera, Transform {});

    /* Car */
    ResourceManager::loadModel("car", "../res/assets/car/car.obj");
    Entity car = ecs.CreateEntity();
    ecs.AddComponent(car, Transform {});
    ecs.AddComponent(car, ModelComponent { .model = ResourceManager::getModel("car") });
    ecs.AddComponent(car, Material { .shaderName = "default" });
}