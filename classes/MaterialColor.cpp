//
// Created by aca on 8.2.21..
//

#include "MaterialColor.h"

MaterialColor::MaterialColor(float shininess, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
    : Material{shininess}, ambient{ambient}, diffuse{diffuse}, specular{specular} { }

void MaterialColor::activate(const Shader &shader, const std::string &prefix) const {
    Material::activate(shader, prefix);
    shader.setUniform3fv(prefix + ".ambient", ambient);
    shader.setUniform3fv(prefix + ".diffuse", diffuse);
    shader.setUniform3fv(prefix + ".specular", specular);
}