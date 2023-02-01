#pragma once
#include "../values.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../../src/Shaders/Shader.h"
#include <iostream>
#include <set>

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

const GLfloat squarpoints[] = {
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f
};

const GLfloat trianglepoint[] = {
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
};

enum ObjectType3D {CUBE, PIRAMID, TETRA, SQUAR3D};
enum ObjectType2D {SQUAR, TRIANGLE};

class Primitive2D {
    public:
        Primitive2D(ObjectType2D Type);
        ~Primitive2D() = default;
        void Draw(std::shared_ptr<Shader::ShaderProgramm> Shad);
        void setCords(glm::vec2 UserCords);
        void setMaterial(glm::vec3 UserMaterial) { material = UserMaterial; }
        void setAngle(glm::vec4 UserAngle) { angle = UserAngle; }
        void setScale(glm::vec2 UserScale);
        glm::vec2 getCords() { return cords; }
        glm::vec2 getSize() { return scale; }
        glm::vec3 getMaterial() { return material; }
    private:
        GLuint VBO, VAO, Shader;
        glm::vec2 scale;
        glm::mat4 model;
        glm::vec2 cords;
        glm::vec3 material;
        glm::vec4 angle;
        int countOfPoints;
};

class Primitive3D {
    public:
        Primitive3D(ObjectType3D Type);
        ~Primitive3D() = default;
        void Draw(std::shared_ptr<Shader::ShaderProgramm> Shad);
        void setCords(glm::vec3 UserCords) { cords = UserCords; }
        void setMaterial(glm::vec4 UserMaterial) { material = UserMaterial; }
        void setAngle(glm::vec4 UserAngle) { angle = UserAngle; }
    protected:
        GLuint VBO, VAO, Shader;
        glm::mat4 model;
        glm::vec3 cords;
        glm::vec4 material;
        glm::vec4 angle;
        int countOfPoints;
};

class SkyBox {
    public:
        SkyBox();
        ~SkyBox() = default;
        void Draw(std::shared_ptr<Shader::ShaderProgramm> Shad);
    private:
        GLuint VBO, VAO;
        glm::mat4 model;
};