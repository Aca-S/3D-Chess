//
// Created by aca on 3.2.21..
//

#ifndef RG_3D_SAH_POINTLIGHT_H
#define RG_3D_SAH_POINTLIGHT_H

#include "Light.h"

class PointLight: public Light {
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
public:
    PointLight(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
               const glm::vec3 &position, float constant, float linear, float quadratic);
    void activate(const Shader &shader, const std::string &prefix) const override;

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    float getConstant() const;

    void setConstant(float constant);

    float getLinear() const;

    void setLinear(float linear);

    float getQuadratic() const;

    void setQuadratic(float quadratic);
};


#endif //RG_3D_SAH_POINTLIGHT_H
