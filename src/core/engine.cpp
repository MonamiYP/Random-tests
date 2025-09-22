#include "Engine.hpp"

void Engine::Run() {
    Init();

    while (!glfwWindowShouldClose(state.window)) {
        float currentTime = glfwGetTime();
        state.deltaTime = currentTime - state.lastTime;
        state.lastTime = currentTime;

        Update();
        ProcessInput();
        Render();

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Engine::Init() {
    state.window = window.setupWindow();
    if (!state.window) throw std::runtime_error("Failed to create window");

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    input = new Input(camera);
    window.setupCallbacks(state.window, input);

    imGUI = new ImGUI(state.window);

    std::string vertex_source = shader.ParseShader("../res/shaders/basic.vertex");
    std::string fragment_source = shader.ParseShader("../res/shaders/basic.fragment");
    shader.CreateShaderProgram(vertex_source, fragment_source);

    light = Light(glm::vec3(1.0f, 1.0f, 5.0f), glm::vec3(1.0f, 0.8f, 0.8f));
    shader.SetLight(light);

    carModel.LoadModel("../res/assets/car/car.obj");
}

void Engine::Update() {
    shader.Bind();
    shader.SetMatrix4("u_view", camera->GetCameraView());
    shader.SetMatrix4("u_projection", camera->GetCameraProjection());
}

void Engine::ProcessInput() {
    input->processInput(state);
}

void Engine::Render() {
    renderer.Clear();

    if(state.guiEnable) { imGUI->drawGUI(); };

    carModel.Draw(shader);
}