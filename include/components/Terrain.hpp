#pragma once

#include <string>

struct Terrain {
    float radius = 10.0f;
    float resolution = 5;
    std::string shaderName;

    float testValue = 1.0f;

    // Noise settings
    float lacunarity = 1.0f;
    float persistence = 0.5f;
    float amplitude = 0.01f;
};