#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_vertexArrayID));
    GLCall(glBindVertexArray(m_vertexArrayID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_vertexArrayID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    Bind();
    vb.Bind();

    const auto& attributes = layout.GetAttributes();
    unsigned int offset = 0;
    for (unsigned int attribute_location = 0; attribute_location < attributes.size(); attribute_location++) {
        const auto& attribute = attributes[attribute_location];
        GLCall(glEnableVertexAttribArray(attribute_location));
        GLCall(glVertexAttribPointer(attribute_location, attribute.size, attribute.type, attribute.normalised, layout.GetStride(), (void*)(size_t)offset)); // Defines layout of a single vertex attribute in currently bound VBO and associates it with currently bound VAO
        offset += attribute.size * sizeof(attribute.type); // Advance offset to the next attribute in the vertex
    }
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_vertexArrayID));
}

void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}