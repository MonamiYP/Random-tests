#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
    private:
        unsigned int m_shaderProgramID;
        std::unordered_map<std::string, int> m_uniformLocationCache;

        std::string ShaderTypeToString(GLenum type);

    public:
        Shader() {}
        ~Shader();

        void Bind() const;
        void Unbind() const;

        unsigned int CompileShader(unsigned int type, const std::string& source);
        std::string ParseShader(const std::string& filepath);
        void CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

        int GetUniformLocation(const std::string& name);
        void SetFloat(const std::string& name, const float value);
        void SetInt(const std::string& name, const int value);
        void SetVector3(const std::string& name, const glm::vec3& vector);
        void SetVector3(const std::string& name, const float v1, const float v2, const float v3);
        void SetVector4(const std::string& name, const glm::vec4& vector);
        void SetVector4(const std::string& name, const float v1, const float v2, const float v3, const float v4);
        void SetMatrix4(const std::string& name, const glm::mat4& matrix);
};