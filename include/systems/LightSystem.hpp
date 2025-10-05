#pragma once

#include "ECS.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"

#include "Light.hpp"
#include "Transform.hpp"

class LightSystem : public System {
    public:
        void setupShaders();
    private:
        void addLightToShader(Shader* shader);
};