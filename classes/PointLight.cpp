//
// Created by aca on 3.2.21..
//

#include "PointLight.h"

PointLight::PointLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                       const glm::vec3 &position, float constant, float linear, float quadratic)
                       : Light{ambient, diffuse, specular},
                       position{position}, constant{constant}, linear{linear}, quadratic{quadratic} { }

void PointLight::activate(const Shader &shader, const std::string &prefix) const {
    Light::activate(shader, prefix);
    shader.setUniform3fv(prefix + ".position", position);
    shader.setUniform1f(prefix + ".constant", constant);
    shader.setUniform1f(prefix + ".linear", linear);
    shader.setUniform1f(prefix + ".quadratic", quadratic);
}

const glm::vec3 &PointLight::getPosition() const {
    return position;
}

void PointLight::setPosition(const glm::vec3 &position) {
    PointLight::position = position;
}

float PointLight::getConstant() const {
    return constant;
}

void PointLight::setConstant(float constant) {
    PointLight::constant = constant;
}

float PointLight::getLinear() const {
    return linear;
}

void PointLight::setLinear(float linear) {
    PointLight::linear = linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}

void PointLight::setQuadratic(float quadratic) {
    PointLight::quadratic = quadratic;
}
