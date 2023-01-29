#include "values.h"

bool menu = false;

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

glm::vec3 lightPos(6.0f, 1.0f, 2.0f);

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);