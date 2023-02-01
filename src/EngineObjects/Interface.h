#pragma once
#include "EnginePrimitives.h"
#include "Text.h"
#include <string>

class Button {
public:
    Button(void (*action)());
    ~Button() = default;
    void setSize(glm::vec2 UserSize);
    void setMaterial(glm::vec3 UserMaterial);
    void setCords(glm::vec2 UserCords);
    void Draw(std::shared_ptr<Shader::ShaderProgramm> ShadVisual, std::shared_ptr<Shader::ShaderProgramm> ShadText);
    void setString(std::string STR, float Userscale, glm::vec3 Usercolor) { this->ButtonText.setText(STR); this->ButtonText.setSize(Userscale); this->ButtonText.setColor(Usercolor); }
    void Press();
    void unPress();
private:
    glm::vec3 oldmaterial;
    Text ButtonText = Text("", 0, 0, 10, glm::vec3(1.0f, 1.0f, 1.0f));
    Primitive2D Visual = Primitive2D(SQUAR);
    void (*PressAction) ();
};