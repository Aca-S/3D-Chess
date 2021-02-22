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

const Texture2D &MaterialTexture::getDiffuse() const {
    return diffuse;
}

void MaterialTexture::setDiffuse(const Texture2D &diffuse) {
    MaterialTexture::diffuse = diffuse;
}

const Texture2D &MaterialTexture::getSpecular() const {
    return specular;
}

void MaterialTexture::setSpecular(const Texture2D &specular) {
    MaterialTexture::specular = specular;
}
