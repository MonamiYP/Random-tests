#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "EngineConfig.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"
#include "Model.hpp"
#include "ImGUI.hpp"
#include "ECS.hpp"

#include "Transform.hpp"
#include "Camera.hpp"
#include "CameraSystem.hpp"
#include "RenderSystem.hpp"

class Engine {    
    public:
        Engine() {}
        ~Engine() {}

        void Run();

    private:
        EngineConfig m_config;
        Window m_window;
        ImGUI m_imGUI;

        Light m_light;

        Entity m_camera;

        void Init();
        void Update();
        void ProcessInput();
        void Render();

        void RegisterComponents();
        void RegisterSystems();
        void CreateEntities();

        std::shared_ptr<CameraSystem> m_cameraSystem;
        std::shared_ptr<RenderSystem> m_renderSystem;
};