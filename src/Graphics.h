//
// Created by mateuszp on 1/19/24.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

#include "GraphicsShader.h"
#include "ComputeShader.h"

class Graphics {
public:
    Graphics();

    void init();

    void run();

    void cleanup();

private:
    const std::vector<float> quad = {
            0.0f, 1.0f,
            1.0f, -1.0f,
            -1.0f, -1.0f
    };

    const int NUM_PARTICLES = 1000000;

    GLFWwindow *window;

    uint32_t win_width = 1200, win_height = 800;

    std::vector<glm::vec3> translations;

    GraphicsShader *particle_renderer_shader;

    uint32_t quad_vao, quad_vbo, instance_pos_ssbo, instance_col_ssbo;

    ComputeShader* compute_particles;
};


#endif //GRAPHICS_H
