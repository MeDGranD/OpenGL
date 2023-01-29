#include "EnginePrimitives.h"

Primitive2D::Primitive2D(ObjectType2D Type){

    if (Type == SQUAR) { this->countOfPoints = 6; }
    if (Type == TRIANGLE) { this->countOfPoints = 3; }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if (Type == SQUAR) { glBufferData(GL_ARRAY_BUFFER, sizeof(squarpoints), squarpoints, GL_STATIC_DRAW); }
    if (Type == TRIANGLE) { glBufferData(GL_ARRAY_BUFFER, sizeof(trianglepoint), trianglepoint, GL_STATIC_DRAW); }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void Primitive2D::Draw(std::shared_ptr<Shader::ShaderProgramm> Shad) {

    glm::vec2 DrawCords = glm::vec2(cords.x * 2 / windowSizeX - 0.5f, -(cords.y / windowSizeY) * 2 + 0.5f);

    GLfloat Userx = scale.x * 2 / windowSizeX;
    GLfloat Usery = scale.y * 2 / windowSizeY;
    DrawCords = glm::vec2(DrawCords.x + (Userx - 1.0f) / 2, DrawCords.y + (-Usery + 1.0f) / 2);

    glm::vec2 DrawScale = glm::vec2(Userx, Usery);

    this->Shader = Shad->getID();

    GLuint Color = glGetUniformLocation(this->Shader, "material");
    GLuint Model = glGetUniformLocation(this->Shader, "model");
    glUniform3f(Color, material.x, material.y, material.z);
    glUniformMatrix4fv(Model, 1, GL_FALSE, glm::value_ptr(model));

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(DrawCords.x, DrawCords.y, 0.0f));
    model = glm::rotate(model, glm::radians(angle.w), glm::vec3(angle.x, angle.y, angle.z));
    model = glm::scale(model, glm::vec3(DrawScale.x, DrawScale.y, 0.0f));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, countOfPoints);

}

void Primitive2D::setCords(glm::vec2 UserCords) { cords = UserCords;}

void Primitive2D::setScale(glm::vec2 UserScale) {
    scale = UserScale;
}

Primitive3D::Primitive3D(ObjectType3D Type) {

    if (Type == CUBE){ this->countOfPoints = 36; }
    if (Type == PIRAMID) { this->countOfPoints = 18; }
    if (Type == TETRA) { this->countOfPoints = 12; }
    if (Type == SQUAR3D) { this->countOfPoints = 6; }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if (Type == CUBE) { glBufferData(GL_ARRAY_BUFFER, sizeof(cubepoints), cubepoints, GL_STATIC_DRAW); }
    if (Type == PIRAMID) { glBufferData(GL_ARRAY_BUFFER, sizeof(piramidpoints), piramidpoints, GL_STATIC_DRAW); }
    if (Type == TETRA) { glBufferData(GL_ARRAY_BUFFER, sizeof(tetrapoints), tetrapoints, GL_STATIC_DRAW); }
    if (Type == SQUAR3D) { glBufferData(GL_ARRAY_BUFFER, sizeof(squarpoints), squarpoints, GL_STATIC_DRAW); }
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void Primitive3D::Draw(std::shared_ptr<Shader::ShaderProgramm> Shad) {

    this->Shader = Shad->getID();

    GLint cudeColor = glGetUniformLocation(this->Shader, "cudeColor");
    GLuint specularLoc = glGetUniformLocation(this->Shader, "specInt");
    GLuint modelLoc = glGetUniformLocation(this->Shader, "model");

    model = glm::mat4(1.0f);
    model = glm::translate(model, cords);
    model = glm::rotate(model, glm::radians(angle.w), glm::vec3(angle.x, angle.y, angle.z));

    glUniform3f(cudeColor, material.x, material.y, material.z);
    glUniform1i(specularLoc, material.w);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, countOfPoints);

}

SkyBox::SkyBox() {

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

void SkyBox::Draw(std::shared_ptr<Shader::ShaderProgramm> Shad){

    GLuint modelLoc = glGetUniformLocation(Shad->getID(), "model");

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(200.0f));

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

}