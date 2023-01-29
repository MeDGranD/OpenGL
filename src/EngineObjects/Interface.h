#pragma once
#include "EnginePrimitives.h"

class Button {
public:
    Button(void (*action)());
    ~Button() = default;
    void setSize(glm::vec2 UserSize);
    void setMaterial(glm::vec3 UserMaterial);
    void setCords(glm::vec2 UserCords);
    void Draw(std::shared_ptr<Shader::ShaderProgramm> Shad);
    void Press();
    void unPress();
private:
    Primitive2D Visual = Primitive2D(SQUAR);
    void (*PressAction) ();
};