#include "ShaderManager.hpp"

std::unordered_map<std::string, std::unique_ptr<Shader>> ShaderManager::m_shaders;

Shader* ShaderManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
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

Shader* ShaderManager::getShader(const std::string& name) {
    auto i = m_shaders.find(name);
    if (i != m_shaders.end()) return i->second.get();

    return nullptr;
}