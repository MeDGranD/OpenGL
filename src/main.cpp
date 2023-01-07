#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders/Shader.h"
#include "Resources/ResourceManager.h"
#include "EngineObjects/EnginePrimitives.h"

GLfloat windowSizeX = 1600;
GLfloat windowSizeY = 800;

glm::vec3 cameraPos = glm::vec3(6.0f, 0.0f, 9.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLfloat lastX = 800, lastY = 400;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
bool firstMouse = true;

GLfloat fov = 45.0f;

glm::vec3 lightPos(6.0f, 1.0f, 2.0f); //Свет

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

void glfwWindowSizeCallBack(GLFWwindow* window, int x, int y);
void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char** argv) {

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(windowSizeX, windowSizeY, "Engine", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallBack);
    glfwSetKeyCallback(window, glfwKeyCallBack);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) return -1;
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    {
        ResourceManager resourceManager(argv[0]);

        auto pLightShaderProgramm = resourceManager.loadShader("LightShader", "res/Shaders/vertexShader.txt", "res/Shaders/lightFragmentShader.txt");
        if (!pLightShaderProgramm) { std::cerr << "Can`t create shader programm!" << std::endl;  return -1; }
        auto pDefaultShaderProgramm = resourceManager.loadShader("DefaultShader", "res/Shaders/vertexShader.txt", "res/Shaders/fragmentShader.txt");
        if (!pDefaultShaderProgramm) { std::cerr << "Can`t create shader programm!" << std::endl; return -1; }

        GLuint lightVAO;
        GLuint VBO;
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubepoints), cubepoints, GL_STATIC_DRAW);

        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        Cube c;
        Piramid p;
        Tetra t;

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            
            pDefaultShaderProgramm->use();

            GLint lightPosLoc = glGetUniformLocation(pDefaultShaderProgramm->getID(), "lightPos");
            GLint viewPosition = glGetUniformLocation(pDefaultShaderProgramm->getID(), "viewPos");
            GLint lightColor = glGetUniformLocation(pDefaultShaderProgramm->getID(), "lightColor");
            glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
            glUniform3f(viewPosition, cameraPos.x, cameraPos.y, cameraPos.z);
            glUniform3f(lightColor, 1.0f, 1.0f, 1.0f);

            GLuint modelLoc = glGetUniformLocation(pDefaultShaderProgramm->getID(), "model");
            GLuint viewLoc = glGetUniformLocation(pDefaultShaderProgramm->getID(), "view");
            GLuint projectionLoc = glGetUniformLocation(pDefaultShaderProgramm->getID(), "projection");
            GLuint specularLoc = glGetUniformLocation(pDefaultShaderProgramm->getID(), "specInt");

            for (int i = 0; i < 5; i++) {

                p.Draw(glm::vec4(0.33f * ((i + 1) % 4), 0.33f * ((i + 1) % 3), 0.33f * ((i + 1) % 2), 50 * i + 2), glm::vec3(3.0f * i, 3.0f, 0.0f),
                    glm::vec3(0.33f * ((i + 1) % 4), 0.33f * ((i + 1) % 3), 0.33f * ((i + 1) % 2)), pDefaultShaderProgramm);

                t.Draw(glm::vec4(0.33f * ((i + 1) % 4), 0.33f * ((i + 1) % 2), 0.33f * ((i + 1) % 3), 50 * i + 2), glm::vec3(3.0f * i, -3.0f, 0.0f),
                    glm::vec3(0.33f * ((i + 1) % 4), 0.33f * ((i + 1) % 2), 0.33f * ((i + 1) % 3)), pDefaultShaderProgramm);

                c.Draw(glm::vec4(0.33f * ((i + 1) % 2), 0.33f * ((i + 1) % 3), 0.33f * ((i + 1) % 4), 50 * i + 2), glm::vec3(3.0f * i, 0.0f, 0.0f), 
                       glm::vec3(0.33f * ((i + 1) % 2), 0.33f * ((i + 1) % 3), 0.33f * ((i + 1) % 4)), pDefaultShaderProgramm);

            }

            view = glm::mat4(1.0f);
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(fov), windowSizeX / windowSizeY, 0.1f, 100.0f);

            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));



            pLightShaderProgramm->use();

            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));

            modelLoc = glGetUniformLocation(pLightShaderProgramm->getID(), "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            viewLoc = glGetUniformLocation(pLightShaderProgramm->getID(), "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

            projectionLoc = glGetUniformLocation(pLightShaderProgramm->getID(), "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glBindVertexArray(0);

            glfwSwapBuffers(window);

            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glfwPollEvents();
            do_movement();
        }
    }
    glfwTerminate();
    return 0;
}

void glfwWindowSizeCallBack(GLFWwindow* window, int x, int y) {

    windowSizeX = x;
    windowSizeY = y;
    glViewport(0, 0, windowSizeX, windowSizeY);

}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GL_TRUE); }

    if (action == GLFW_PRESS)
        keys[key] = true;

    else if (action == GLFW_RELEASE)
        keys[key] = false;

}

void do_movement() {

    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keys[GLFW_KEY_W])
        cameraPos += cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_S])
        cameraPos -= cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_A])
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_LEFT_SHIFT])
        cameraPos += glm::vec3(0.0f, -cameraSpeed, 0.0f);
    if (keys[GLFW_KEY_SPACE])
        cameraPos += glm::vec3(0.0f, cameraSpeed, 0.0f);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}