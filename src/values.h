#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include <set>
#include "EngineObjects/EnginePrimitives.h"

extern bool menu;

extern GLfloat windowSizeX;
extern GLfloat windowSizeY;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern bool keys[1024];

extern GLfloat deltaTime;
extern GLfloat lastFrame;

extern GLfloat lastX, lastY;
extern GLfloat yaw;
extern GLfloat pitch;
extern bool firstMouse;

extern GLfloat fov;

extern glm::vec3 lightPos;

extern glm::mat4 model;
extern glm::mat4 view;
extern glm::mat4 projection;