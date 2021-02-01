//
// Created by aca on 30.1.21..
//

#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "error.h"

static std::string readFile(const std::string &path) {
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    int success = 0;
    char errLog[512];

    std::string vs = readFile(vertexShaderPath);
    const char *vertexShaderSource = vs.c_str();
    unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, errLog);
        std::cerr << errLog << std::endl;
        CHECK_ERROR(0, "Vertex shader compilation failed");
    }

    std::string fs = readFile(fragmentShaderPath);
    const char *fragmentShaderSource = fs.c_str();
    unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, errLog);
        std::cerr << errLog << std::endl;
        CHECK_ERROR(0, "Fragment shader compilation failed");
    }

    sp_id = glCreateProgram();
    glAttachShader(sp_id, vertexShader);
    glAttachShader(sp_id, fragmentShader);
    glLinkProgram(sp_id);
    glGetProgramiv(sp_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(sp_id, 512, nullptr, errLog);
        std::cerr << errLog << std::endl;
        CHECK_ERROR(0, "Shader program linkage failed");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(sp_id);
}

void Shader::del() {
    glDeleteProgram(sp_id);
    sp_id = -1;
}

void Shader::setUniform1f(const std::string &uniformName, float x) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform1f(uniformId, x);
}

void Shader::setUniform2f(const std::string &uniformName, float x, float y) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform2f(uniformId, x, y);
}

void Shader::setUniform3f(const std::string &uniformName, float x, float y, float z) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform3f(uniformId, x, y, z);
}

void Shader::setUniform4f(const std::string &uniformName, float x, float y, float z, float w) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform4f(uniformId, x, y, z, w);
}

void Shader::setUniform1i(const std::string &uniformName, int x) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform1i(uniformId, x);
}

void Shader::setUniform2i(const std::string &uniformName, int x, int y) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform2i(uniformId, x, y);
}

void Shader::setUniform3i(const std::string &uniformName, int x, int y, int z) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform3i(uniformId, x, y, z);
}

void Shader::setUniform4i(const std::string &uniformName, int x, int y, int z, int w) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniform4i(uniformId, x, y, z, w);
}

void Shader::setUniformMatrix4fv(const std::string &uniformName, const glm::mat4 &matrix) const {
    int uniformId = glGetUniformLocation(sp_id, uniformName.c_str());
    glUniformMatrix4fv(uniformId, 1, false, glm::value_ptr(matrix));
}