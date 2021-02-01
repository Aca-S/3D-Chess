//
// Created by aca on 30.1.21..
//

#include "Texture2D.h"

#include <stb_image.h>
#include <iostream>

#include "error.h"

Texture2D::Texture2D(const std::string &texturePath, GLenum filtering, GLenum sampling) {
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, filtering);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampling);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampling);

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nChannels, 0);
    CHECK_ERROR(data != nullptr, "Failed to load image from file");

    switch(nChannels)
    {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        default:
            CHECK_ERROR(0, "Number of channels not supported");
            break;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture2D::active(GLenum e) const {
    glActiveTexture(e);
    glBindTexture(GL_TEXTURE_2D, tex_id);
}

void Texture2D::del() {
    glDeleteTextures(1, &tex_id);
    tex_id = -1;
}