#pragma once

#include "Shader.hpp"
#include <string>
#include <unordered_map>

class ShaderManager {
    public:
        static Shader* loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        static Shader* getShader(const std::string& name);
        static void clear() { m_shaders.clear(); }
    private:
        static std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
};