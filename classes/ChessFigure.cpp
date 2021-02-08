//
// Created by aca on 3.2.21..
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ChessFigure.h"

ChessFigure::ChessFigure(Model *model, std::pair<int, int> position, type figure_type, color figure_color) {
    this->model = model;
    this->position = position;
    this->figure_type = figure_type;
    this->figure_color = figure_color;
}

void ChessFigure::draw(Shader &shader, MaterialColor &white, MaterialColor &black) {
    glm::mat4 model = glm::mat4(1.0);
    // Raise the figures a bit along the y axis so they don't cut into the board
    float elevation = 0;
    switch(figure_type)
    {
        case PAWN:
            elevation = 0.162f;
            break;
        case ROOK:
            elevation = 0.232f;
            break;
        case KNIGHT:
            elevation = 0.312f;
            break;
        case BISHOP:
            elevation = 0.262f;
            break;
        case QUEEN:
            elevation = 0.328f;
            break;
        case KING:
            elevation = 0.33f;
            break;
    }
    if(figure_status == ACTIVE)
        elevation += 0.5f;
    model = glm::translate(model, glm::vec3(position.first * 0.5, elevation, position.second * 0.5));
    // If the color is white, rotate the figures 180 degrees (don't want the knights from both players facing the same direction)
    if(figure_color == WHITE)
    {
        model = glm::rotate(model, (float)glm::radians(180.0), glm::vec3(0.0f, 1.0f, 0.0f));
        white.activate(shader);
    }
    else
        black.activate(shader);
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    shader.setUniformMatrix4fv("model", model);
    this->model->draw(shader);
}