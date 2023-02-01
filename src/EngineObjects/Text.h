#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include "../Shaders/Shader.h"
#include "../values.h"

struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

std::map<char, Character> CreateCharMap();

class Text {
	public:
		Text(std::string STR, float Userx, float Usery, float Userscale, glm::vec3 Usercolor);
		~Text() = default;
		void setText(std::string str) { TextSTR = str; }
		void setSize(float Userscale) { this->scale = (1.0f / 35) * Userscale; }
		void setCords(float Userx, float Usery) { this->x = Userx; this->y = Usery; }
		void setColor(glm::vec3 Usercolor) { this->color = Usercolor; }
		void Draw(std::shared_ptr<Shader::ShaderProgramm> Shad);
		float getScale() { return this->scale; }
	private:
		unsigned VAO, VBO, Shader;
		std::string TextSTR;
		glm::vec3 color;
		std::map<char, Character> Characters;
		float x, y, scale;
};