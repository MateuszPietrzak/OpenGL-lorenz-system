//
// Created by mateuszp on 1/19/24.
//

#include <random>
#include "Graphics.h"

#include "GraphicsShader.h"

Graphics::Graphics() {
}

void Graphics::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(win_width, win_height, "OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("No window");
    }
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        Graphics *graphics = (Graphics *) glfwGetWindowUserPointer(window);
        graphics->win_width = width;
        graphics->win_height = height;

        glViewport(0, 0, graphics->win_width, graphics->win_height);
    });

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Sad no glad :(");
    }

    glViewport(0, 0, win_width, win_height);

    glEnable(GL_DEPTH_TEST);

    translations.resize(NUM_PARTICLES);
    std::mt19937 rand(2);
    std::uniform_real_distribution<float> dist(-300.0, 300.0);
    for (int i = 0; i < NUM_PARTICLES; i++) {
        while (glm::distance(translations[i], glm::vec3(0.0f, 0.0f, 0.0f)) <= 1.0) {
            translations[i] = glm::vec3(dist(rand), dist(rand), dist(rand));
        }
    }

    particle_renderer_shader = new GraphicsShader("assets/shaders/instance.vert", "assets/shaders/instance.frag");

    particle_renderer_shader->use();


    glGenVertexArrays(1, &quad_vao);
    glGenBuffers(1, &quad_vbo);
    glGenBuffers(1, &instance_pos_ssbo);
    glGenBuffers(1, &instance_col_ssbo);

    glBindVertexArray(quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);

    glBufferData(GL_ARRAY_BUFFER, quad.size() * sizeof(quad.front()), quad.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, instance_pos_ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec3) * NUM_PARTICLES, &translations[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, instance_pos_ssbo);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, instance_col_ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec3) * NUM_PARTICLES, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, instance_col_ssbo);

    compute_particles = new ComputeShader("assets/shaders/compute_particles.glsl");
    compute_particles->use();
    compute_particles->setFloat("speed", 0.1);
}

void Graphics::run() {
    while (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    double frame_start = glfwGetTime();
    double frame_end = glfwGetTime();
    double  delta_t = 0.0;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        compute_particles->use();
        compute_particles->setFloat("delta_time", delta_t);

        glDispatchCompute(NUM_PARTICLES / LOCAL_SIZE, 1, 1);

        particle_renderer_shader->use();

        glm::mat4 model = glm::mat4(1.0);
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        glm::mat4 camera = glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f),
                                       glm::vec3(0.0f, 0.0f, 0.0f),
                                       glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) win_width / win_height, 1.0f, 1000.0f);

        particle_renderer_shader->setMat4("projection", projection);
        particle_renderer_shader->setMat4("view", camera);
        particle_renderer_shader->setMat4("model", model);
        glBindVertexArray(quad_vao);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, NUM_PARTICLES);

        glfwSwapBuffers(window);
        glfwPollEvents();

        frame_end = glfwGetTime();
        delta_t = frame_end - frame_start;
        frame_start = frame_end;
    }
}

void Graphics::cleanup() {
    glfwTerminate();
}
