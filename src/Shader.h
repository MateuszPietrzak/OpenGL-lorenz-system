//
// Created by mateuszp on 1/20/24.
//

#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <cstdint>
#include <string>

class Shader {
public:
    static std::string readFile(std::string &path);

    void use();

    void setInt(std::string var_name, int val);

    void setFloat(std::string var_name, float val);

    void setVec2(std::string var_name, glm::vec2 val);

    void setMat4(std::string var_name, glm::mat4 val);

protected:
    uint32_t shader_id;
};


#endif //COMPUTE_SHADER_H
