#include "Text.h"

std::map<char, Character> CreateCharMap() {

	std::map<char, Character> Characters;
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) { std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl; }

	FT_Face face;
	if (FT_New_Face(ft, "C:/GitRepos/OpenGL/src/EngineObjects/arial.ttf", 0, &face)) { std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl; }

	FT_Set_Pixel_Sizes(face, 0, 48);

	for (unsigned int i = 0; i < 128; i++) {

		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<unsigned int>(face->glyph->advance.x)
		};
		Characters.insert(std::pair<char, Character>(i, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return Characters;
}

Text::Text(std::string STR, float Userx, float Usery, float Userscale, glm::vec3 Usercolor) {

	this->TextSTR = STR;
	this->x = Userx;
	this->y = Usery;
	this->scale = (1.0f / 35) * Userscale;
	this->color = Usercolor;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	this->Characters = CreateCharMap();

}

void Text::Draw(std::shared_ptr<Shader::ShaderProgramm> Shad) {

	this->Shader = Shad->getID();
	Shad->use();
	glUniformMatrix4fv(glGetUniformLocation(this->Shader, "projection"), 1, GL_FALSE, glm::value_ptr(glm::ortho(0.0f, windowSizeX, 0.0f, windowSizeY)));
	glUniform3f(glGetUniformLocation(this->Shader, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	float oldx = this->x;
	std::string::const_iterator c;
	for (c = TextSTR.begin(); c != TextSTR.end(); c++) {

		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = windowSizeY - (y - (ch.Size.y - ch.Bearing.y) * scale);

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->x = oldx;
}