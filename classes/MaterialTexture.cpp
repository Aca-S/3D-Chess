//
// Created by aca on 3.2.21..
//

#include "MaterialTexture.h"

MaterialTexture::MaterialTexture(float shininess, const Texture2D &diffuse, const Texture2D &specular)
    : Material{shininess}, diffuse{diffuse}, specular{specular} { }

void MaterialTexture::activate(const Shader &shader, const std::string &prefix) const {
    Material::activate(shader, prefix);
    diffuse.active(GL_TEXTURE0);
    shader.setUniform1i(prefix + ".texture_diffuse1", 0);
    specular.active(GL_TEXTURE1);
    shader.setUniform1i(prefix + ".texture_specular1", 1);
}