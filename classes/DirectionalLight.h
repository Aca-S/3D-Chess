//
// Created by aca on 3.2.21..
//

#ifndef RG_3D_SAH_DIRECTIONALLIGHT_H
#define RG_3D_SAH_DIRECTIONALLIGHT_H

#include <glm/glm.hpp>

#include "Shader.h"

class DirectionalLight {
public:
    DirectionalLight(const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
    void activate(const Shader &shader);

    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


#endif //RG_3D_SAH_DIRECTIONALLIGHT_H
