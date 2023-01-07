#include "ResourceManager.h"
#include "../../src/Shaders/Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executablePath) {

	size_t found = executablePath.find_last_of("/\\");
	path = executablePath.substr(0, found);

	found = path.find_last_of("/\\");
	path = path.substr(0, found);
	found = path.find_last_of("/\\");
	path = path.substr(0, found);

}

std::string ResourceManager::getPath() { return path; }

std::string ResourceManager::getFileString(const std::string& relativePath) const {

	std::ifstream f;
	f.open(path + '/' + relativePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open()) {

		std::cerr << "failed to open file : " << relativePath << std::endl;
		return std::string{};

	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();

}

std::shared_ptr<Shader::ShaderProgramm> ResourceManager::loadShader(const std::string& shaderName,
																	const std::string& vertexPath, const std::string& fragmentPath) {

	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty()) { std::cerr << "No vertex shader!" << std::endl; }
	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty()) { std::cerr << "No fragment shader!" << std::endl; }

	std::shared_ptr<Shader::ShaderProgramm>& newShader = shaderProgramms.emplace(shaderName, 
																				std::make_shared<Shader::ShaderProgramm>(vertexString, 
																														 fragmentString)).first->second;
	if (newShader->isCompiled()) { return newShader; }
	std::cerr << "Can`t load shader programm : \n" << "Vertex : " << vertexPath << "\n Fragment : " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<Shader::ShaderProgramm> ResourceManager::getShader(const std::string shaderName) {

	ShaderProgrammsMap::const_iterator it = shaderProgramms.find(shaderName);
	if (it != shaderProgramms.end()) { return it->second; }
	std::cerr << "Can`t find the shader : " << shaderName << std::endl;
	return nullptr;
}