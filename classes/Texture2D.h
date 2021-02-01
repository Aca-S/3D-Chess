//
// Created by aca on 30.1.21..
//

#ifndef RG_3D_SAH_TEXTURE2D_H
#define RG_3D_SAH_TEXTURE2D_H

#include <string>
#include <glad/glad.h>

class Texture2D {
    unsigned tex_id;
public:
    Texture2D(const std::string &texturePath, GLenum filtering, GLenum sampling);
    void active(GLenum e) const;
    void del();
};


#endif //RG_3D_SAH_TEXTURE2D_H
