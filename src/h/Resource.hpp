#pragma once

#include <string>
#include <memory>
#include <map>

namespace Core {

	class Shader;

}

	class Resource {

	public:

		Resource(const std::string& executablePath);
		~Resource() = default;

		Resource(const Resource&) = delete;
		Resource& operator=(const Resource&) = delete;
		Resource& operator=(Resource&&) = delete;
		Resource(Resource&&) = delete;

		std::shared_ptr<Core::Shader> shaderLoad(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<Core::Shader> shaderGet(const std::string& shaderName);

	private:

		std::string getFileString(const std::string& relativeFilePath) const;

		typedef std::map<const std::string, std::shared_ptr<Core::Shader>> ShaderMap;
		ShaderMap m_shader;

		std::string m_path;
	};

