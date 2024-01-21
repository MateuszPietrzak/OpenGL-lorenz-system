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
