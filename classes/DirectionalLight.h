//
// Created by aca on 3.2.21..
//

#ifndef RG_3D_SAH_DIRECTIONALLIGHT_H
#define RG_3D_SAH_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight: public Light {
    glm::vec3 direction;
public:
    DirectionalLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                     const glm::vec3 &direction);
    void activate(const Shader &shader, const std::string &prefix) const override;

    const glm::vec3 &getDirection() const;

    void setDirection(const glm::vec3 &direction);
};


#endif //RG_3D_SAH_DIRECTIONALLIGHT_H
