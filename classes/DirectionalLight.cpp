//
// Created by aca on 3.2.21..
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const std::string &prefix, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                 const glm::vec3 &direction)
                 : Light{prefix, ambient, diffuse, specular},
                 direction{direction} { }

DirectionalLight::DirectionalLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                                   const glm::vec3 &direction)
                                   : Light{ambient, diffuse, specular},
                                   direction{direction} { }

void DirectionalLight::activate(const Shader &shader) const {
    Light::activate(shader);
    shader.setUniform3fv(Light::getPrefix() + ".direction", direction);
}

void DirectionalLight::activate(const Shader &shader, const std::string &prefix) const {
    Light::activate(shader, prefix);
    shader.setUniform3fv(prefix + ".direction", direction);
}

const glm::vec3 &DirectionalLight::getDirection() const {
    return direction;
}

void DirectionalLight::setDirection(const glm::vec3 &direction) {
    DirectionalLight::direction = direction;
}
