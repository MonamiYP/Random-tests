#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "EngineConfig.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "ShaderManager.hpp"
#include "Model.hpp"
#include "ImGUI.hpp"
#include "ECS.hpp"

#include "Transform.hpp"
#include "Camera.hpp"
#include "CameraSystem.hpp"

class Engine {    
    public:
        Engine() {}
        ~Engine() {}

        void Run();

    private:
        EngineConfig m_config;
        Window m_window;
        Renderer m_renderer;
        ImGUI m_imGUI;

        Light m_light;
        Model m_carModel;

        Entity m_camera;

        void Init();
        void Update();
        void ProcessInput();
        void Render();

        void RegisterComponents();
        void RegisterSystems();
        void CreateEntities();

        std::shared_ptr<CameraSystem> m_cameraSystem;
};