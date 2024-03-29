//
// Created by aca on 19.2.21..
//

#include "Light.h"

Light::Light(const std::string &prefix, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
    : prefix{prefix}, ambient{ambient}, diffuse{diffuse}, specular{specular} { }

Light::Light(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
    : ambient{ambient}, diffuse{diffuse}, specular{specular} {
        prefix = "light";
    }

void Light::activate(const Shader &shader) const {
    shader.setUniform3fv(Light::prefix + ".ambient", ambient);
    shader.setUniform3fv(Light::prefix + ".diffuse", diffuse);
    shader.setUniform3fv(Light::prefix + ".specular", specular);
}

void Light::activate(const Shader &shader, const std::string &prefix) const {
    shader.setUniform3fv(prefix + ".ambient", ambient);
    shader.setUniform3fv(prefix + ".diffuse", diffuse);
    shader.setUniform3fv(prefix + ".specular", specular);
}

const glm::vec3 &Light::getAmbient() const {
    return ambient;
}

void Light::setAmbient(const glm::vec3 &ambient) {
    Light::ambient = ambient;
}

const glm::vec3 &Light::getDiffuse() const {
    return diffuse;
}

void Light::setDiffuse(const glm::vec3 &diffuse) {
    Light::diffuse = diffuse;
}

const glm::vec3 &Light::getSpecular() const {
    return specular;
}

void Light::setSpecular(const glm::vec3 &specular) {
    Light::specular = specular;
}

const std::string &Light::getPrefix() const {
    return prefix;
}

void Light::setPrefix(const std::string &prefix) {
    Light::prefix = prefix;
}
