//
// Created by mateuszp on 1/20/24.
//

#include <fstream>
#include <sstream>
#include "Shader.h"

std::string Shader::readFile(std::string &path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open file!");
    }

    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

void Shader::use() {
    glUseProgram(shader_id);
}

void Shader::setInt(std::string var_name, int val) {
    glUniform1i(glGetUniformLocation(shader_id, var_name.c_str()), val);
}

void Shader::setFloat(std::string var_name, float val) {
    glUniform1f(glGetUniformLocation(shader_id, var_name.c_str()), val);
}

void Shader::setVec2(std::string var_name, glm::vec2 val) {
    glUniform2f(glGetUniformLocation(shader_id, var_name.c_str()), val.x, val.y);
}

void Shader::setMat4(std::string var_name, glm::mat4 val) {
    glUniformMatrix4fv(glGetUniformLocation(shader_id, var_name.c_str()), 1, GL_FALSE, &val[0][0]);
}

