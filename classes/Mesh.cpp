//
// Created by aca on 1.2.21..
//

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned> &indices, std::vector<Texture2D> &textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMesh();
}

void Mesh::draw(Shader &shader) {
    int diffuseNr = 1;
    int specularNr = 1;
    int normalNr = 1;
    int heightNr = 1;

    for(int i = 0; i < textures.size(); i++)
    {
        std::string name = textures[i].getTextureTypeString();
        switch(textures[i].getTextureType())
        {
            case DIFFUSE:
                name += std::to_string(diffuseNr++);
                break;
            case SPECULAR:
                name += std::to_string(specularNr++);
                break;
            case NORMAL:
                name += std::to_string(normalNr++);
                break;
            case HEIGHT:
                name += std::to_string(heightNr++);
                break;
        }
        shader.setUniform1i(name, i);
        textures[i].active(GL_TEXTURE0 + i);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tangent));
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, bitangent));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);
}