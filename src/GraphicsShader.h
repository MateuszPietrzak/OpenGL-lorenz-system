//
// Created by mateuszp on 1/19/24.
//

#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>

#include <glm/glm.hpp>
#include "Shader.h"


class GraphicsShader: public Shader{
public:
    GraphicsShader(std::string vert_path, std::string frag_path);

    void setInt(std::string var_name, int val);
    void setVec2(std::string var_name, glm::vec2 val);
    void setMat4(std::string var_name, glm::mat4 val);
private:
};



#endif //SHADER_H
