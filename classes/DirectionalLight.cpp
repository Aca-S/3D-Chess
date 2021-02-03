//
// Created by aca on 3.2.21..
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular) {
    this->direction = direction;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void DirectionalLight::activate(const Shader &shader) {
    shader.setUniform3fv("directionalLight.direction", direction);
    shader.setUniform3fv("directionalLight.ambient", ambient);
    shader.setUniform3fv("directionalLight.diffuse", diffuse);
    shader.setUniform3fv("directionalLight.specular", specular);
}