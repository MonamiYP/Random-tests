#include "VertexBuffer.hpp"
#include "Renderer.hpp"
#include "stdio.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, GLenum usage_type) {
    GLCall(glGenBuffers(1, &m_vertexBufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID)); // GL_ARRAY_BUFFER is buffer type for VBO
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage_type)); // Allocate GPU memory and add data. Default is GL_STATIC_DRAW for data that is set only once and used many times.
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_vertexBufferID));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID));
}

void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}