//
// Created by aca on 3.2.21..
//

#include "SpotLight.h"

SpotLight::SpotLight(const glm::vec3 &position, const glm::vec3 &direction,
          const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
          float cutOff, float constant, float linear, float quadratic) {
    this->position = position;
    this->direction = direction;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->cutOff = glm::cos(glm::radians(cutOff));
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}
void SpotLight::activate(const Shader &shader) {
    shader.setUniform3fv("spotLight.position", position);
    shader.setUniform3fv("spotLight.direction", direction);
    shader.setUniform3fv("spotLight.ambient", ambient);
    shader.setUniform3fv("spotLight.diffuse", diffuse);
    shader.setUniform3fv("spotLight.specular", specular);
    shader.setUniform1f("spotLight.cutOff", cutOff);
    shader.setUniform1f("spotLight.constant", constant);
    shader.setUniform1f("spotLight.linear", linear);
    shader.setUniform1f("spotLight.quadratic", quadratic);
}