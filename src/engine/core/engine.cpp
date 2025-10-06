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

    ResourceManager::loadResources();

    RegisterComponents();
    RegisterSystems();
    CreateEntities();

    m_lightSystem->setupShaders();
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

    if(!m_config.guiEnable) { 
        m_cameraSystem->Update(m_config.deltaTime);
    }
    auto& camera_camera = ecs.GetComponent<Camera>(m_camera);
    auto& camera_transform = ecs.GetComponent<Transform>(m_camera);

    Shader* shader_default = ResourceManager::getShader("default");
    shader_default->Bind();
    shader_default->SetMatrix4("u_view", camera_camera.viewMatrix);
    shader_default->SetMatrix4("u_projection", camera_camera.projectionMatrix);
    shader_default->SetVector3("u_viewPos", camera_transform.position);

    Shader* shader_light = ResourceManager::getShader("singleColor");
    shader_light->Bind();
    shader_light->SetMatrix4("u_view", camera_camera.viewMatrix);
    shader_light->SetMatrix4("u_projection", camera_camera.projectionMatrix);

    Shader* shader_terrain = ResourceManager::getShader("terrain");
    shader_terrain->Bind();
    shader_terrain->SetMatrix4("u_view", camera_camera.viewMatrix);
    shader_terrain->SetMatrix4("u_projection", camera_camera.projectionMatrix);
    shader_terrain->SetVector3("u_viewPos", camera_transform.position);

    InputManager::Get().resetMouse();
}

void Engine::ProcessInput() {
    InputManager::Get().processInput(m_window.getWindow(), m_config.deltaTime);
}

void Engine::Render() {
    m_renderSystem->clear();
    m_imGUI.startFrame();

    m_terrainSystem->render();
    m_renderSystem->render();

    if(m_config.guiEnable) { 
        m_imGUI.drawGUI();
        m_terrainSystem->renderGUI();
    };
    m_imGUI.endFrame();
}

void Engine::RegisterComponents() {
    ecs.RegisterComponent<Transform>();
    ecs.RegisterComponent<Camera>();
    ecs.RegisterComponent<ModelComponent>();
    ecs.RegisterComponent<Material>();
    ecs.RegisterComponent<Terrain>();
    ecs.RegisterComponent<Light>();
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

    m_terrainSystem = ecs.RegisterSystem<TerrainSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<Transform>());
        signature.set(ecs.GetComponentType<Terrain>());
        ecs.SetSystemSignature<TerrainSystem>(signature);
    }

    m_lightSystem = ecs.RegisterSystem<LightSystem>();
    {
        Signature signature;
        signature.set(ecs.GetComponentType<Light>());
        ecs.SetSystemSignature<LightSystem>(signature);
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

    /* Directional Light */
    Entity directionalLight = ecs.CreateEntity();
    ecs.AddComponent(directionalLight, Light { .type = LightCasterType::Directional });

    /* Terrain */
    Entity terrain = ecs.CreateEntity();
    ecs.AddComponent(terrain, Transform { .position = glm::vec3(210.0f, 0.0f, 0.0f) });
    ecs.AddComponent(terrain, Terrain { .shaderName = "terrain", .radius = 200.0f, .resolution = 20 });
    m_terrainSystem->generateVertices();
}