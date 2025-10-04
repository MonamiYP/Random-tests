#pragma once

#include "ECS.hpp"
#include "components/Transform.hpp"
#include "ResourceManager.hpp"

#include "Light.hpp"
#include "Transform.hpp"

class LightSystem : public System {
    public:
        void setupShaderLights();
};