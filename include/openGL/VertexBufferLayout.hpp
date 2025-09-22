#pragma once

#include <glad/glad.h>
#include <vector>
#include <stdexcept>

/*
    Structure representing a single vertex attribute in the layout
    - type: OpenGL enum for the data type (e.g., GL_FLOAT)
    - size: Number of components in the attribute (e.g., 3 for vec3)
    - normalized: Whether the data should be normalized when sent to the shader
*/ 
struct VertexBufferAttributes {
    unsigned int type;
    unsigned int size;
    unsigned char normalised;
};

class VertexBufferLayout {
    private:
        std::vector<VertexBufferAttributes> m_attributes;
        unsigned int m_stride;
    public:
        VertexBufferLayout() : m_stride(0) {}

        void AddAttribute(unsigned int type, unsigned int size, unsigned char normalized = GL_FALSE) {
            m_attributes.push_back({ type, size, normalized });
            m_stride += sizeof(type) * size;
        }

        void IgnoreAttribute(unsigned int type, unsigned int size) {
            m_stride += sizeof(type) * size;
        }

        inline const std::vector<VertexBufferAttributes> GetAttributes() const& { return m_attributes; }
        inline unsigned int GetStride() const { return m_stride; }
};