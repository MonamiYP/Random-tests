#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Shader.hpp"
#include "ResourceManager.hpp"
#include "Window.hpp"

class ShadowMap {
    private:
        const unsigned int WIDTH = 1024, HEIGHT = 1024; // Resolution
        
        unsigned int m_fbo = 0;
        unsigned int m_shadowMap = 0;

        unsigned int createFrameBuffer();
        unsigned int createDepthTexture();

    public:
        void init();

        unsigned int getDepthMap() { return m_shadowMap; }

        void prepareShadowRender(glm::vec3 lightPos);

        void attachTextureToFBO();
        void bindFrameBuffer();
        void unbindFrameBuffer(Window* window);
};