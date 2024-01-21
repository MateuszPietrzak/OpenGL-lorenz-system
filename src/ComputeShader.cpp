//
// Created by mateuszp on 1/20/24.
//

#include <stdexcept>
#include "ComputeShader.h"

ComputeShader::ComputeShader(std::string compute_path) {
    std::string compute_code = readFile(compute_path);

    const char *compute_cstr = compute_code.c_str();

    uint32_t compute_shader;
    int success;
    char info_log[512];
    compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute_shader, 1, &compute_cstr, nullptr);
    glCompileShader(compute_shader);
    glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(compute_shader, 512, nullptr, info_log);
        throw std::runtime_error(info_log);
    }

    shader_id = glCreateProgram();
    glAttachShader(shader_id, compute_shader);
    glLinkProgram(shader_id);
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_id, 512, nullptr, info_log);
        throw std::runtime_error(info_log);
    }
    glDeleteShader(compute_shader);
}
