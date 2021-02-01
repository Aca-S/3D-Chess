//
// Created by aca on 30.1.21..
//

#ifndef RG_3D_SAH_SHADER_H
#define RG_3D_SAH_SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
    unsigned sp_id;
public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    void use() const;
    void del();

    void setUniform1f(const std::string &uniformName, float x) const;
    void setUniform2f(const std::string &uniformName, float x, float y) const;
    void setUniform3f(const std::string &uniformName, float x, float y, float z) const;
    void setUniform4f(const std::string &uniformName, float x, float y, float z, float w) const;

    void setUniform1i(const std::string &uniformName, int x) const;
    void setUniform2i(const std::string &uniformName, int x, int y) const;
    void setUniform3i(const std::string &uniformName, int x, int y, int z) const;
    void setUniform4i(const std::string &uniformName, int x, int y, int z, int w) const;

    void setUniformMatrix4fv(const std::string &uniformName, const glm::mat4 &matrix) const;
};


#endif //RG_3D_SAH_SHADER_H
