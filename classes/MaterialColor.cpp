//
// Created by aca on 8.2.21..
//

#include "MaterialColor.h"

MaterialColor::MaterialColor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}

void MaterialColor::activate(Shader &shader) const {
    shader.setUniform3fv("material.ambient", ambient);
    shader.setUniform3fv("material.diffuse", diffuse);
    shader.setUniform3fv("material.specular", specular);
    shader.setUniform1f("material.shininess", shininess);
}