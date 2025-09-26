#include "ResourceManager.hpp"

std::unordered_map<std::string, std::unique_ptr<Shader>> ResourceManager::m_shaders;
std::unordered_map<std::string, std::unique_ptr<Model>> ResourceManager::m_models;

Shader* ResourceManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    auto i = m_shaders.find(name);
    if (i != m_shaders.end()) { // Shader already added to list
        return i->second.get();
    }

    auto shader = std::make_unique<Shader>();
    Shader* shaderPtr = shader.get();
    std::string vertex_source = shaderPtr->ParseShader(vertexPath);
    std::string fragment_source = shaderPtr->ParseShader(fragmentPath);
    shaderPtr->CreateShaderProgram(vertex_source, fragment_source);
    m_shaders[name] = std::move(shader);

    return shaderPtr;
}

Shader* ResourceManager::getShader(const std::string& name) {
    auto i = m_shaders.find(name);
    if (i != m_shaders.end()) return i->second.get();

    return nullptr;
}

Model* ResourceManager::loadModel(const std::string& name, const std::string& path) {
    auto i = m_models.find(name);
    if (i != m_models.end()) { // Model already added to list
        return i->second.get();
    }

    auto model = std::make_unique<Model>();
    Model* modelPtr = model.get();
    modelPtr->LoadModel(path);
    
    m_models[name] = std::move(model);

    return modelPtr;
}

Model* ResourceManager::getModel(const std::string& name) {
    auto i = m_models.find(name);
    if (i != m_models.end()) return i->second.get();

    return nullptr;
}