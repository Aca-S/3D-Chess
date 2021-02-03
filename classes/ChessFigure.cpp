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

void ChessFigure::draw(Shader &shader) {
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(position.first * 0.5, 0.0f, position.second * 0.5));
    if(figure_color == WHITE)
        model = glm::rotate(model, (float)glm::radians(180.0), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    shader.setUniformMatrix4fv("model", model);
    this->model->draw(shader);
}