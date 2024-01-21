//
// Created by mateuszp on 1/19/24.
//

#include "GraphicsShader.h"

#include <fstream>
#include <iostream>
#include <sstream>

GraphicsShader::GraphicsShader(std::string vert_path, std::string frag_path) {
    std::string vert_code = readFile(vert_path);
    std::string frag_code = readFile(frag_path);


    const char *vert_cstr = vert_code.c_str();
    const char *frag_cstr = frag_code.c_str();

    uint32_t vertex_shader, fragment_shader;
    int success;
    char info_log[512];
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vert_cstr, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        throw std::runtime_error(info_log);
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_cstr, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        throw std::runtime_error(info_log);
    }

    shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex_shader);
    glAttachShader(shader_id, fragment_shader);
    glLinkProgram(shader_id);
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_id, 512, nullptr, info_log);
        throw std::runtime_error(info_log);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void GraphicsShader::setInt(std::string var_name, int val) {
    glUniform1i(glGetUniformLocation(shader_id, var_name.c_str()), val);
}

void GraphicsShader::setVec2(std::string var_name, glm::vec2 val) {
    glUniform2f(glGetUniformLocation(shader_id, var_name.c_str()), val.x, val.y);
}

void GraphicsShader::setMat4(std::string var_name, glm::mat4 val) {
    glUniformMatrix4fv(glGetUniformLocation(shader_id, var_name.c_str()), 1, GL_FALSE, &val[0][0]);
}

