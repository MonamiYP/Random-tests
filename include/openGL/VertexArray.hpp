#pragma once

#include <glad/glad.h>
#include "VertexBuffer.hpp"

/*
    The vertex array object stores vertex attributes. It stores:
    - Calls to glEnableVertexAttribArray or glDisableVertexAttribArray
    - Vertex attribute configurations via glVertexAttribPointer
    - Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer

*/

class VertexBufferLayout;

class VertexArray {
    private:
        unsigned int m_vertexArrayID;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void Bind() const;
        void Unbind() const;
};