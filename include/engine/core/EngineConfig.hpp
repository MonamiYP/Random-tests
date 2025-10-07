#pragma once

struct EngineConfig {
    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    bool guiEnable = false;

    float windowWidth = 1200.0f;
    float windowHeight = 800.0f;
};