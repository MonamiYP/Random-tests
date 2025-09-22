#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

#include <string>
#include <vector>

struct MeshVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct MeshTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
    private:
        unsigned int m_VAO, m_VBO, m_IBO;

        std::vector<MeshVertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<MeshTexture> m_textures;

        void setupMesh();

    public:
        Mesh(std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices, std::vector<MeshTexture>& textures) : m_vertices(vertices), m_indices(indices), m_textures(textures) { setupMesh(); }
        ~Mesh() {};

        void Draw(Shader &shader);
};