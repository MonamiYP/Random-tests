#include "Shader.hpp"
#include "Renderer.hpp"

Shader::~Shader() {
    GLCall(glDeleteProgram(m_shaderProgramID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_shaderProgramID));
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    m_shaderProgramID = program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // Returns pointer to data in std::string
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // Compiler error handling
    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:" << ShaderTypeToString(type) << ":COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

std::string Shader::ShaderTypeToString(GLenum type) {
    switch (type) {
        case GL_VERTEX_SHADER: return "VERTEX";
        case GL_FRAGMENT_SHADER: return "FRAGMENT";
        case GL_TESS_CONTROL_SHADER: return "TESSELLATION CONTROL";
        case GL_TESS_EVALUATION_SHADER: return "TESSELLATION EVALUTAION";
        case GL_GEOMETRY_SHADER: return "GEOMETRY";
        case GL_COMPUTE_SHADER: return "COMPUTE";
        default: return "UNKNOWN";
    }
}

std::string Shader::ParseShader(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }

    std::string str;
    std::string content;

    while (std::getline(file, str)) {
        content.append(str + "\n");
    }

    return content;
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    int location = glGetUniformLocation(m_shaderProgramID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist" << std::endl;
    
    m_uniformLocationCache[name] = location;
    return location;
}

void Shader::SetFloat(const std::string& name, const float value) {
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetInt(const std::string& name, const int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetVector3(const std::string& name, const glm::vec3& vector) {
    GLCall(glUniform3fv(GetUniformLocation(name), 1, &vector[0]));
}

void Shader::SetVector3(const std::string& name, const float v1, const float v2, const float v3) {
    GLCall(glUniform3f(GetUniformLocation(name), v1, v2, v3));
}

void Shader::SetVector4(const std::string& name, const glm::vec4& vector) {
    GLCall(glUniform4fv(GetUniformLocation(name), 1, &vector[0]));
}

void Shader::SetVector4(const std::string& name, const float v1, const float v2, const float v3, const float v4) {
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}

void Shader::SetMatrix4(const std::string& name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}