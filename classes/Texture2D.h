//
// Created by aca on 30.1.21..
//

#ifndef RG_3D_SAH_TEXTURE2D_H
#define RG_3D_SAH_TEXTURE2D_H

#include <string>
#include <glad/glad.h>

enum texType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT
};

class Texture2D {
    unsigned tex_id;
    texType tex_type;
public:
    Texture2D(const std::string &texturePath, texType type, GLenum filtering, GLenum sampling);
    void active(GLenum e) const;
    void del();

    texType getTextureType() const;
    std::string getTextureTypeString() const;
};


#endif //RG_3D_SAH_TEXTURE2D_H
