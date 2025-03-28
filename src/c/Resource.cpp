#include "../h/Resource.hpp"
#include "../h/Shader.hpp"

#include<sstream>
#include<fstream>
#include<iostream>

	Resource::Resource(const std::string& executablePath) {

		size_t found = executablePath.find_last_of("/\\");
		m_path = executablePath.substr(0, found);

	}

	std::string Resource::getFileString(const std::string& relativeFilePath) const {

		std::ifstream f;
		f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);

		if (!f.is_open()) {

			std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
			return std::string{};
		}

		std::stringstream buffer;
		buffer << f.rdbuf();
		return buffer.str();
	}

	std::shared_ptr<Core::Shader> Resource::shaderLoad(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath) {

		std::string vertexString = getFileString(vertexPath);

		if (vertexString.empty()) {

			std::cerr << "No vertex shader!" << std::endl;
			return 0;
		}

		std::string fragmentString = getFileString(fragmentPath);

		if (fragmentString.empty()) {

			std::cerr << "No fragment shader!" << std::endl;
			return 0;
		}

		std::shared_ptr<Core::Shader>& newShader = m_shader.emplace(shaderName, std::make_shared< Core::Shader>(vertexString, fragmentString)).first->second;

		if (newShader->isCompiled()) {

			return newShader;
		}
		std::cerr << "Can't load shader program: \n"
			<< "Vertex: " << vertexPath << "\n"
			<< "Fragment: " << fragmentPath << std::endl;

		return 0;
	}

	std::shared_ptr<Core::Shader> Resource::shaderGet(const std::string& shaderName) {

		ShaderMap::const_iterator it = m_shader.find(shaderName);

		if (it != m_shader.end()) {

			return it->second;
		}

		std::cerr << "Can't find the shader program: " << shaderName << std::endl;
		return 0;
	}
