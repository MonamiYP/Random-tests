#pragma once

#include "ECS.hpp"
#include "components/Camera.hpp"
#include "components/Transform.hpp"

#include "InputManager.hpp"

/*
    Some note on coordinate systems:    
    - view matrix: transforms the world coordinates to view-space coordinates in such a way that each coordinate is as seen from the camera's point of view. 
    - projection matrix: project view-space coordinates to clip coordinates (-1.0 and 1.0 range, determine which vertices will end up on the screen). Projection to clip-space coordinates can add perspective if using perspective projection. 
*/

class CameraSystem : public System {
    public:
        void Update(float deltaTime);

        void ProcessKeyboardInput(InputManager& input, float deltaTime);
        void ProcessMouseInput(InputManager& input, float deltaTime);
        
    private:
        void UpdateVectors();
};