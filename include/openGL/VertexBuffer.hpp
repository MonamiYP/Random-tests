#pragma once
#include <glad/glad.h>

/*
    The vertex buffer object stores large number of vertices in the GPU's memory
    Sends large batches of data to the graphics card at once
*/

class VertexBuffer {
    private:
        unsigned int m_vertexBufferID; // Store OpenGL generated ID that uniquely identifies VBO on the GPU
    public:
        VertexBuffer(const void* data, unsigned int size, GLenum usage_type = GL_STATIC_DRAW);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
};