#pragma once

#include <string>

/* Noise settings */
struct FractalSettings {
    float amplitude   = 0.0f;
    float frequency   = 0.1f;
    float lacunarity  = 1.0f;
    float persistence = 0.5f;
};

struct RidgeSettings {
    float amplitude   = 0.0f;
    float frequency   = 0.1f;
    float lacunarity  = 1.0f;
    float persistence = 0.5f;
};

/* Terrain */

struct Terrain {
    float radius = 10.0f;
    float floorDepth = 0.0001f;
    float resolution = 5;

    FractalSettings fractal;
    RidgeSettings   ridge;
};