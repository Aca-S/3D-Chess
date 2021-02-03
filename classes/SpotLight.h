//
// Created by aca on 3.2.21..
//

#ifndef RG_3D_SAH_SPOTLIGHT_H
#define RG_3D_SAH_SPOTLIGHT_H

#include <glm/glm.hpp>

#include "Shader.h"

class SpotLight {
public:
    SpotLight(const glm::vec3 &position, const glm::vec3 &direction,
              const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
              float cutOff, float constant, float linear, float quadratic);
    void activate(const Shader &shader);

    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float cutOff;
    float constant;
    float linear;
    float quadratic;
};


#endif //RG_3D_SAH_SPOTLIGHT_H
