#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "EngineConfig.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Model.hpp"
#include "ImGUI.hpp"
#include "ECS.hpp"

class Engine {    
    public:
        Engine() : m_input(m_camera) {}
        ~Engine() {}

        void Run();

    private:
        EngineConfig m_config;
        ECS m_ecs;
        Window m_window;
        Renderer m_renderer;
        ImGUI m_imGUI;

        Camera m_camera;
        Input m_input;

        Shader m_shader;
        Light m_light;
        Model m_carModel;

        void Init();
        void Update();
        void ProcessInput();
        void Render();
};