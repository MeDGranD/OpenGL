#pragma once

#include <glad/glad.h>
#include <string>

namespace Shader {
	class ShaderProgramm {
	public:
		ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgramm();
		bool isCompiled() { return is_Compiled; }
		void use();
		GLuint getID() { return ID; }
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool is_Compiled = false;
		GLuint ID = 0;
	};
}