//
// Created by aca on 1.2.21..
//

#ifndef RG_3D_SAH_MESH_H
#define RG_3D_SAH_MESH_H

#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"
#include "Texture2D.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class Mesh {
    unsigned VBO, EBO, VAO;
    void setupMesh();
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<Texture2D> textures;
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned> &indices, std::vector<Texture2D> &textures);
    void draw(Shader &shader);
};


#endif //RG_3D_SAH_MESH_H
