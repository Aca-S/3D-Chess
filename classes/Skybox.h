//
// Created by aca on 6.2.21..
//

#ifndef RG_3D_SAH_SKYBOX_H
#define RG_3D_SAH_SKYBOX_H

#include <string>
#include <vector>
#include <glad/glad.h>

class Skybox {
    unsigned tex_id;
    unsigned VBO, VAO;
public:
    Skybox(const std::vector<std::string> &facePaths);
    void draw() const;
    void del();
};


#endif //RG_3D_SAH_SKYBOX_H
