//
// Created by aca on 3.2.21..
//

#ifndef RG_3D_SAH_MATERIAL_H
#define RG_3D_SAH_MATERIAL_H

#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture2D.h"

class Material {
    Texture2D *diffuse;
    Texture2D *specular;
public:
    Material(Texture2D *diffuse, Texture2D *specular, float shininess);
    void activate(Shader &shader) const;
    float shininess;
};


#endif //RG_3D_SAH_MATERIAL_H
