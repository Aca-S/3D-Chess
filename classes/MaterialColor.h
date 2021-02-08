//
// Created by aca on 8.2.21..
//

#ifndef RG_3D_SAH_MATERIALCOLOR_H
#define RG_3D_SAH_MATERIALCOLOR_H

#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture2D.h"

class MaterialColor {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
public:
    MaterialColor(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess);
    void activate(Shader &shader) const;
    float shininess;
};


#endif //RG_3D_SAH_MATERIALCOLOR_H
