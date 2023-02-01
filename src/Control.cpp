#include "Control.h"
#include "values.h"

void glfwWindowSizeCallBack(GLFWwindow* window, int x, int y) {

    windowSizeX = x;
    windowSizeY = y;

}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GL_TRUE); }
    if (key == GLFW_KEY_H && action == GLFW_PRESS) { menu = true; glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

    if (action == GLFW_PRESS)
        keys[key] = true;

    else if (action == GLFW_RELEASE)
        keys[key] = false;

}

void do_movement() {

    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (!menu) {
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
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    std::cout << xpos << '\t' << ypos << std::endl;

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    if (!menu) yaw += xoffset;
    if (!menu) pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    if (!menu) cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

void initControl(GLFWwindow* window) {

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallBack);
    glfwSetKeyCallback(window, glfwKeyCallBack);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);

}