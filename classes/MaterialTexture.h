//
// Created by aca on 3.2.21..
//

#ifndef RG_3D_SAH_MATERIALTEXTURE_H
#define RG_3D_SAH_MATERIALTEXTURE_H

#include "Material.h"
#include <glm/glm.hpp>
#include "Texture2D.h"

class MaterialTexture: public Material {
    Texture2D diffuse;
    Texture2D specular;
public:
    MaterialTexture(float shininess, const Texture2D &diffuse, const Texture2D &specular);
    void activate(const Shader &shader, const std::string &prefix) const override;

    const Texture2D &getDiffuse() const;

    void setDiffuse(const Texture2D &diffuse);

    const Texture2D &getSpecular() const;

    void setSpecular(const Texture2D &specular);
};


#endif //RG_3D_SAH_MATERIALTEXTURE_H
