#pragma once

#include <memory>
#include <string>
#include <map>
#include "../../src/Shaders/Shader.h"

class ResourceManager {
	public:
		ResourceManager(const std::string& executablePath);
		~ResourceManager() = default;

		std::string getPath();
		std::shared_ptr<Shader::ShaderProgramm> loadShader(const std::string& shaderName,
														   const std::string& vertexPath, 
														   const std::string& fragmentPath);
		std::shared_ptr<Shader::ShaderProgramm> getShader(const std::string shaderName);
	private:
		std::string getFileString(const std::string& relativePath) const;
		
		typedef std::map<const std::string, std::shared_ptr<Shader::ShaderProgramm>> ShaderProgrammsMap;
		ShaderProgrammsMap shaderProgramms;

		std::string path;
};