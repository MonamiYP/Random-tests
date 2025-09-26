#pragma once

#include "core/ECS.hpp"
#include "components/ModelComponent.hpp"
#include "components/Transform.hpp"

class ModelRenderSystem : public System {
    public:
        void Draw();  
};