//
// Created by aca on 19.2.21..
//

#ifndef RG_3D_SAH_MATERIAL_H
#define RG_3D_SAH_MATERIAL_H

#include "Shader.h"

class Material {
    float shininess;
public:
    explicit Material(float shininess);
    virtual void activate(const Shader &shader, const std::string &prefix) const = 0;
};


#endif //RG_3D_SAH_MATERIAL_H
