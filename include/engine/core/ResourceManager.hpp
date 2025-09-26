#pragma once

#include "Shader.hpp"
#include "Model.hpp"
#include <string>
#include <unordered_map>

class ResourceManager {
    public:
        static Shader* loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        static Shader* getShader(const std::string& name);
        
        static Model* loadModel(const std::string& name, const std::string& path);
        static Model* getModel(const std::string& name);

        static void clear() { m_shaders.clear(); m_models.clear(); }
    private:
        static std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
        static std::unordered_map<std::string, std::unique_ptr<Model>> m_models;
};