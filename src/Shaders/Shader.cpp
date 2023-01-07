#include "Shader.h"
#include <iostream>

namespace Shader {

	ShaderProgramm::ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader) {

		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {

			std::cerr << "VERTEX SHADER COMPILE ERROR" << std::endl;

		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {

			std::cerr << "FRAGMENT SHADER COMPILE ERROR" << std::endl;
			glDeleteShader(vertexShaderID);

		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShaderID);
		glAttachShader(ID, fragmentShaderID);
		glLinkProgram(ID);

		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if(!success){
		
			GLchar infoLog[1024];
			glGetShaderInfoLog(ID, 1014, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: LINK TIME ERROR: \n" << infoLog << std::endl;

		}
		else { is_Compiled = true; }

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

	}

	bool ShaderProgramm::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {

		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, NULL);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {

			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1014, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: COMPILE TIME ERROR: \n" << infoLog << std::endl;
			return false;

		}
		return true;
	}

	ShaderProgramm::~ShaderProgramm() { glDeleteProgram(ID); }

	void ShaderProgramm::use(){ glUseProgram(ID); }

}