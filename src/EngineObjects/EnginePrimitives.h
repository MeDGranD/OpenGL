#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../../src/Shaders/Shader.h"
#include <iostream>

const GLfloat cubepoints[] = {
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

const GLfloat piramidpoints[] = {
    -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f,  0.5f, 1.0f,
     0.5f, -0.5f, 0.5f, 0.0f,  0.5f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.0f,  0.5f, 1.0f,

    -0.5f, -0.5f,  0.5f, -1.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.5f, 0.0f,
     0.0f,  0.5f,  0.0f, -1.0f, 0.5f, 0.0f,

     0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f,
     0.0f,  0.5f,  0.0f, 1.0f, 0.5f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.5f, -1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.5f, -1.0f,
     0.0f,  0.5f,  0.0f, 0.0f, 0.5f, -1.0f
};

const GLfloat tetrapoints[] = {
    -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
     0.0f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 1.0f,
     0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.5f, 1.0f,

     0.5f, -0.5f,  0.5f, 1.0f, 0.25f, -0.5f,
     0.0f, -0.5f, -0.5f, 1.0f, 0.25f, -0.5f,
     0.0f,  0.5f,  0.0f, 1.0f, 0.25f, -0.5f,

    -0.5f, -0.5f,  0.5f, -1.0f, 0.25f, -0.5f,
     0.0f, -0.5f, -0.5f, -1.0f, 0.25f, -0.5f,
     0.0f,  0.5f,  0.0f, -1.0f, 0.25f, -0.5f
};

class Cube {
    public:
        Cube();
        ~Cube() = default;
        void Draw(glm::vec4 material, glm::vec3 cords, glm::vec3 angle, std::shared_ptr<Shader::ShaderProgramm> Shad);
    private:
        GLuint VBO, VAO;
        glm::mat4 model;
};

class Piramid {
    public:
        Piramid();
        ~Piramid() = default;
        void Draw(glm::vec4 material, glm::vec3 cords, glm::vec3 angle, std::shared_ptr<Shader::ShaderProgramm> Shad);
    private:
        GLuint VBO, VAO;
        glm::mat4 model;
};

class Tetra {
    public:
        Tetra();
        ~Tetra() = default;
        void Draw(glm::vec4 material, glm::vec3 cords, glm::vec3 angle, std::shared_ptr<Shader::ShaderProgramm> Shad);
    private:
        GLuint VBO, VAO;
        glm::mat4 model;
};