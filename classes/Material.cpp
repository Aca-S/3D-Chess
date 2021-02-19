//
// Created by aca on 19.2.21..
//

#include "Material.h"

Material::Material(float shininess)
    : shininess{shininess} { }

void Material::activate(const Shader &shader, const std::string &prefix) const {
    shader.setUniform1f(prefix + ".shininess", shininess);
}