//
// Created by aca on 3.2.21..
//

#include "SpotLight.h"

SpotLight::SpotLight(const std::string &prefix, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                     const glm::vec3 &position, const glm::vec3 &direction,
                     float cutOff, float constant, float linear, float quadratic)
                     : Light{prefix, ambient, diffuse, specular},
                     position{position}, direction{direction},
                     cutOff{glm::cos(glm::radians(cutOff))}, constant{constant}, linear{linear}, quadratic{quadratic} { }

SpotLight::SpotLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                     const glm::vec3 &position, const glm::vec3 &direction,
                     float cutOff, float constant, float linear, float quadratic)
                     : Light{ambient, diffuse, specular},
                     position{position}, direction{direction},
                     cutOff{glm::cos(glm::radians(cutOff))}, constant{constant}, linear{linear}, quadratic{quadratic} { }

void SpotLight::activate(const Shader &shader) const {
    Light::activate(shader);
    shader.setUniform3fv(Light::getPrefix() + ".position", position);
    shader.setUniform3fv(Light::getPrefix() + ".direction", direction);
    shader.setUniform1f(Light::getPrefix() + ".cutOff", cutOff);
    shader.setUniform1f(Light::getPrefix() + ".constant", constant);
    shader.setUniform1f(Light::getPrefix() + ".linear", linear);
    shader.setUniform1f(Light::getPrefix() + ".quadratic", quadratic);
}

void SpotLight::activate(const Shader &shader, const std::string &prefix) const {
    Light::activate(shader, prefix);
    shader.setUniform3fv(prefix + ".position", position);
    shader.setUniform3fv(prefix + ".direction", direction);
    shader.setUniform1f(prefix + ".cutOff", cutOff);
    shader.setUniform1f(prefix + ".constant", constant);
    shader.setUniform1f(prefix + ".linear", linear);
    shader.setUniform1f(prefix + ".quadratic", quadratic);
}

const glm::vec3 &SpotLight::getPosition() const {
    return position;
}

void SpotLight::setPosition(const glm::vec3 &position) {
    SpotLight::position = position;
}

const glm::vec3 &SpotLight::getDirection() const {
    return direction;
}

void SpotLight::setDirection(const glm::vec3 &direction) {
    SpotLight::direction = direction;
}

float SpotLight::getCutOff() const {
    return cutOff;
}

void SpotLight::setCutOff(float cutOff) {
    SpotLight::cutOff = cutOff;
}

float SpotLight::getConstant() const {
    return constant;
}

void SpotLight::setConstant(float constant) {
    SpotLight::constant = constant;
}

float SpotLight::getLinear() const {
    return linear;
}

void SpotLight::setLinear(float linear) {
    SpotLight::linear = linear;
}

float SpotLight::getQuadratic() const {
    return quadratic;
}

void SpotLight::setQuadratic(float quadratic) {
    SpotLight::quadratic = quadratic;
}
