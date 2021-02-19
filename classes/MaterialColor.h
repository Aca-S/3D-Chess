//
// Created by aca on 8.2.21..
//

#ifndef RG_3D_SAH_MATERIALCOLOR_H
#define RG_3D_SAH_MATERIALCOLOR_H

#include "Material.h"
#include <glm/glm.hpp>

class MaterialColor: public Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
public:
    MaterialColor(float shininess, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
    void activate(const Shader &shader, const std::string &prefix) const override;
};


#endif //RG_3D_SAH_MATERIALCOLOR_H
