#include "EnginePrimitives.h"

Cube::Cube() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubepoints), cubepoints, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void Cube::Draw(glm::vec4 material, glm::vec3 cords, glm::vec3 angle, std::shared_ptr<Shader::ShaderProgramm> Shad) {

    GLint cudeColor = glGetUniformLocation(Shad->getID(), "cudeColor");
    GLuint specularLoc = glGetUniformLocation(Shad->getID(), "specInt");
    GLuint modelLoc = glGetUniformLocation(Shad->getID(), "model");

    model = glm::mat4(1.0f);
    model = glm::translate(model, cords);
    model = glm::rotate(model, glm::radians(50.0f * (GLfloat)glfwGetTime()), angle);

    glUniform3f(cudeColor, material.x, material.y, material.z);
    glUniform1i(specularLoc, material.w);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

Piramid::Piramid() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(piramidpoints), piramidpoints, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void Piramid::Draw(glm::vec4 material, glm::vec3 cords, glm::vec3 angle, std::shared_ptr<Shader::ShaderProgramm> Shad) {

    GLint cudeColor = glGetUniformLocation(Shad->getID(), "cudeColor");
    GLuint specularLoc = glGetUniformLocation(Shad->getID(), "specInt");
    GLuint modelLoc = glGetUniformLocation(Shad->getID(), "model");

    model = glm::mat4(1.0f);
    model = glm::translate(model, cords);
    model = glm::rotate(model, glm::radians(45.0f * (GLfloat)glfwGetTime()), angle);

    glUniform3f(cudeColor, material.x, material.y, material.z);
    glUniform1i(specularLoc, material.w);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 18);

    glBindVertexArray(0);

}

Tetra::Tetra() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tetrapoints), tetrapoints, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void Tetra::Draw(glm::vec4 material, glm::vec3 cords, glm::vec3 angle, std::shared_ptr<Shader::ShaderProgramm> Shad) {

    GLint cudeColor = glGetUniformLocation(Shad->getID(), "cudeColor");
    GLuint specularLoc = glGetUniformLocation(Shad->getID(), "specInt");
    GLuint modelLoc = glGetUniformLocation(Shad->getID(), "model");

    model = glm::mat4(1.0f);
    model = glm::translate(model, cords);
    model = glm::rotate(model, glm::radians(45.0f * (GLfloat)glfwGetTime()), angle);

    glUniform3f(cudeColor, material.x, material.y, material.z);
    glUniform1i(specularLoc, material.w);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12);

    glBindVertexArray(0);

}