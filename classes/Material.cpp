//
// Created by aca on 3.2.21..
//

#include "Material.h"

Material::Material(Texture2D *diffuse, Texture2D *specular, float shininess) {
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}

void Material::activate(Shader &shader) const {
    diffuse->active(GL_TEXTURE0);
    shader.setUniform1i("material.texture_diffuse1", 0);
    specular->active(GL_TEXTURE1);
    shader.setUniform1i("material.texture_specular1", 1);
    shader.setUniform1f("material.shininess", shininess);
}