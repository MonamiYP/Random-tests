#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "ApplicationState.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Model.hpp"
#include "ImGUI.hpp"

class Engine {    
    public:
        Engine() {}
        ~Engine() {}

        void Run();

    private:
        ApplicationState state;
        Window window;
        Renderer renderer;
        ImGUI* imGUI;
        Camera* camera;
        Input* input;

        Shader shader;
        Light light;
        Model carModel;

        void Init();
        void Update();
        void ProcessInput();
        void Render();
        void CleanUp();
};