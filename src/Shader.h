//
// Created by mateuszp on 1/20/24.
//

#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include <glad/glad.h>


#include <cstdint>
#include <string>

class Shader {
public:
    uint32_t shader_id;

    static std::string readFile(std::string &path);

    void use();
};


#endif //COMPUTE_SHADER_H
