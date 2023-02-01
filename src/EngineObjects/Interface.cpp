#include "Interface.h"

Button::Button(void (*action)()) {
    this->PressAction = action;
    Visual.setAngle(glm::vec4(1.0f, 1.0f, 1.0f, 0));
}

void Button::setCords(glm::vec2 UserCords) { Visual.setCords(UserCords); }

void Button::setMaterial(glm::vec3 UserMaterial) { Visual.setMaterial(UserMaterial); this->oldmaterial = Visual.getMaterial(); }

void Button::setSize(glm::vec2 UserSize) { Visual.setScale(UserSize); }

void Button::Draw(std::shared_ptr<Shader::ShaderProgramm> ShadVisual, std::shared_ptr<Shader::ShaderProgramm> ShadText) {
    this->ButtonText.setCords(Visual.getCords().x, Visual.getCords().y + ButtonText.getScale()*35);
    Visual.Draw(ShadVisual); 
    ButtonText.Draw(ShadText);
}

void Button::Press() {

    std::cout << "Mouse : " << lastX << '\t' << lastY << std::endl;

    if (lastX >= Visual.getCords().x && lastX <= Visual.getCords().x + Visual.getSize().x && lastY >= Visual.getCords().y && lastY <= Visual.getCords().y + Visual.getSize().y) {

        this->oldmaterial = Visual.getMaterial();
        Visual.setMaterial(glm::vec3(1.0f, 1.0f, 1.0f));
        PressAction();

    }

}

void Button::unPress() { Visual.setMaterial(oldmaterial); }