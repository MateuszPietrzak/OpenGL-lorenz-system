//
// Created by mateuszp on 1/19/24.
//

#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>

#include "Shader.h"


class GraphicsShader: public Shader{
public:
    GraphicsShader(std::string vert_path, std::string frag_path);

private:
};



#endif //SHADER_H
