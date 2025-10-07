#pragma once

#include "ECS.hpp"
#include "components/ModelComponent.hpp"
#include "components/Transform.hpp"
#include "ResourceManager.hpp"

class ShadowMapSystem : public System {
    public:
        void render();
        void clear();
};