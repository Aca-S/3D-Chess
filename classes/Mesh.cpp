//
// Created by aca on 1.2.21..
//

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned> &indices, std::vector<Texture2D> &textures)
    : vertices{vertices}, indices{indices}, textures{textures} {
        setupMesh();
    }

static std::vector<Vertex> rawToVertices(float *verticesRaw, int numOfVertices) {
    std::vector<Vertex> vertices(numOfVertices);
    for(int i = 0; i < numOfVertices; i++)
    {
        int baseIndex = i * 14;
        vertices[i].position = glm::vec3(verticesRaw[baseIndex], verticesRaw[baseIndex + 1], verticesRaw[baseIndex + 2]);
        vertices[i].normal = glm::vec3(verticesRaw[baseIndex + 3], verticesRaw[baseIndex + 4], verticesRaw[baseIndex + 5]);
        vertices[i].texCoords = glm::vec2(verticesRaw[baseIndex + 6], verticesRaw[baseIndex + 7]);
        vertices[i].tangent = glm::vec3(verticesRaw[baseIndex + 8], verticesRaw[baseIndex + 9], verticesRaw[baseIndex + 10]);
        vertices[i].bitangent = glm::vec3(verticesRaw[baseIndex + 11], verticesRaw[baseIndex + 12], verticesRaw[baseIndex + 13]);
    }
    return vertices;
}

static std::vector<unsigned> rawToIndices(unsigned *indicesRaw, int numOfIndices) {
    std::vector<unsigned> indices(numOfIndices);
    for(int i = 0; i < numOfIndices; i++)
        indices[i] = indicesRaw[i];
    return indices;
}

Mesh::Mesh(float *vertices, int numOfVertices, unsigned *indices, int numOfIndices, MaterialTexture &material)
    : vertices{rawToVertices(vertices, numOfVertices)}, indices{rawToIndices(indices, numOfIndices)} {
        Mesh::textures.push_back(material.getDiffuse());
        Mesh::textures.push_back(material.getSpecular());
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