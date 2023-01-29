#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders/Shader.h"
#include "Resources/ResourceManager.h"
#include "values.h"
#include "EngineObjects/EnginePrimitives.h"
#include "EngineObjects/Interface.h"
#include "Control.h"

std::set<Primitive3D*> Objects;
std::set<Button*> ButtonCords;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void CreateSquar3D();

int main(int argc, char** argv) {

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(windowSizeX, windowSizeY, "Engine", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    initControl(window);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) return -1;
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    {
        ResourceManager resourceManager(argv[0]);

        auto pSkyBoxShaderProgramm = resourceManager.loadShader("SkyBoxShader", "res/Shaders/vertexShader.txt", "res/Shaders/skyboxFragmentShader.txt");
        if (!pSkyBoxShaderProgramm) { std::cerr << "Can`t create shader programm!" << std::endl;  return -1; }
        auto pLightShaderProgramm = resourceManager.loadShader("LightShader", "res/Shaders/vertexShader.txt", "res/Shaders/lightFragmentShader.txt");
        if (!pLightShaderProgramm) { std::cerr << "Can`t create shader programm!" << std::endl;  return -1; }
        auto pDefaultShaderProgramm = resourceManager.loadShader("DefaultShader", "res/Shaders/vertexShader.txt", "res/Shaders/fragmentShader.txt");
        if (!pDefaultShaderProgramm) { std::cerr << "Can`t create shader programm!" << std::endl; return -1; }
        auto pDefault2DShaderProgramm = resourceManager.loadShader("Default2DShaderProgramm", "res/Shaders/2DvertexShader.txt", "res/Shaders/2DfragmentShader.txt");
        if (!pDefault2DShaderProgramm) { std::cerr << "Can`t create shader programm!" << std::endl; return -1; }

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

        Primitive3D c(CUBE);
        c.setCords(glm::vec3(7.0f, 0.0f, 6.0f));
        c.setMaterial(glm::vec4(1.0f, 0.0f, 1.0f, 2));
        c.setAngle(glm::vec4(1.0f, 1.0f, 1.0f, 55));

        Primitive3D p(PIRAMID);
        p.setCords(glm::vec3(4.0f, 0.0f, 6.0f));
        p.setMaterial(glm::vec4(1.0f, 0.0f, 1.0f, 2));
        p.setAngle(glm::vec4(1.0f, 1.0f, 1.0f, 55));

        Primitive3D t(TETRA);
        t.setCords(glm::vec3(1.0f, 0.0f, 6.0f));
        t.setMaterial(glm::vec4(1.0f, 0.0f, 1.0f, 2));
        t.setAngle(glm::vec4(1.0f, 1.0f, 1.0f, 55));

        Primitive3D sq(SQUAR3D);
        sq.setCords(glm::vec3(10.0f, 0.0f, 6.0f));
        sq.setMaterial(glm::vec4(1.0f, 0.0f, 1.0f, 2));
        sq.setAngle(glm::vec4(1.0f, 1.0f, 1.0f, 55));

        SkyBox s;
        
        Primitive2D but(SQUAR);
        but.setCords(glm::vec2(0, 0));
        but.setMaterial(glm::vec3(0.33f, 0.33f, 0.33f));
        but.setAngle(glm::vec4(1.0f, 1.0f, 1.0f, 0));
        but.setScale(glm::vec2(1600, 800));

        Button b1(CreateSquar3D);
        b1.setCords(glm::vec2(50, 50));
        b1.setMaterial(glm::vec3(0.5f, 0.2f, 0.3f));
        b1.setSize(glm::vec2(100, 20));
        ButtonCords.insert(&b1);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glDisable(GL_DEPTH_TEST);

            pDefault2DShaderProgramm->use();

            but.Draw(pDefault2DShaderProgramm);
            b1.Draw(pDefault2DShaderProgramm);

            glEnable(GL_DEPTH_TEST);

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

            if (menu) { glViewport((windowSizeX - 1000) / 2, windowSizeY - 562, 1000, 562); }
            else { glViewport(0, 0, windowSizeX, windowSizeY); }

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

            c.Draw(pDefaultShaderProgramm);
            p.Draw(pDefaultShaderProgramm);
            t.Draw(pDefaultShaderProgramm);
            sq.Draw(pDefaultShaderProgramm);

            for (Primitive3D* elem : Objects) {

                elem->Draw(pDefaultShaderProgramm);

            }

            view = glm::mat4(1.0f);
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(fov), windowSizeX / windowSizeY, 0.1f, 800.0f);

            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
            
            pSkyBoxShaderProgramm->use();

            s.Draw(pSkyBoxShaderProgramm);

            view = glm::mat4(1.0f);
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(fov), windowSizeX / windowSizeY, 0.1f, 800.0f);

            viewLoc = glGetUniformLocation(pLightShaderProgramm->getID(), "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

            projectionLoc = glGetUniformLocation(pLightShaderProgramm->getID(), "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
            
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
            
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

            glViewport(0, 0, windowSizeX, windowSizeY);

            glfwSwapBuffers(window);

            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glfwPollEvents();
            do_movement();
        }
    }
    for (Primitive3D* elem : Objects) { delete(elem); }
    glfwTerminate();
    return 0;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

        if (lastX >= (windowSizeX - 1000) / 2 && lastX <= (windowSizeX - 1000) / 2 + 1000 && lastY >= 0 && lastY <= 562) { menu = false; glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
        for (Button* elem : ButtonCords) { elem->Press(); }

    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        for (Button* elem : ButtonCords) { elem->unPress(); }
    }

}

void CreateSquar3D(){

    Primitive3D* newObject = new Primitive3D(CUBE);
    newObject->setCords(cameraPos);
    newObject->setMaterial(glm::vec4(0.1f, 0.2f, 0.3f, 5));
    newObject->setAngle(glm::vec4(1.0f, 1.0f, 1.0f, 0));
    Objects.insert(newObject);

}