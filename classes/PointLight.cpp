//
// Created by aca on 3.2.21..
//

#include "PointLight.h"

PointLight::PointLight(const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float constant, float linear, float quadratic) {
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

void PointLight::activate(const Shader &shader) {
    shader.setUniform3fv("pointLight.position", position);
    shader.setUniform3fv("pointLight.ambient", ambient);
    shader.setUniform3fv("pointLight.diffuse", diffuse);
    shader.setUniform3fv("pointLight.specular", specular);
    shader.setUniform1f("pointLight.constant", constant);
    shader.setUniform1f("pointLight.linear", linear);
    shader.setUniform1f("pointLight.quadratic", quadratic);
}