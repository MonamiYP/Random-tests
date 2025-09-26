#pragma once

#include "ECS.hpp"
#include "components/ModelComponent.hpp"
#include "components/Material.hpp"
#include "components/Transform.hpp"
#include "ResourceManager.hpp"

class RenderSystem : public System {
    public:
        void render();  
        void clear();
};