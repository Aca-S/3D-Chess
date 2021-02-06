//
// Created by aca on 6.2.21..
//

#include "ChessBoard.h"

ChessBoard::ChessBoard() {
    float boardVertices[] = {
            // Coords           Normals        Texture
            -0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0, 0.0f, 0.0f, // bottom-left
            0.5f, -0.5f, 0.0f,  0.0, 0.0, 1.0, 4.0f, 0.0f, // bottom-right
            -0.5f, 0.5f, 0.0f,  0.0, 0.0, 1.0, 0.0f, 4.0f, // top-left
            0.5f, 0.5f, 0.0f,   0.0, 0.0, 1.0, 4.0f, 4.0f  // top-right
    };

    unsigned boardIndices[] = {
            0, 1, 2,
            1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boardVertices), boardVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boardIndices), boardIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ChessBoard::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ChessBoard::del() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}