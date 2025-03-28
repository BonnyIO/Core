#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace Core {

	class Shader {

	public:

		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();
		bool isCompiled() const { return m_isCompiled; }
		void use() const;

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, const GLint value) const;
		void setFloat(const std::string& name, float value) const;
		void setVec2(const std::string& name, const glm::vec2& value) const;
		void setVec2(const std::string& name, float x, float y) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, float x, float y, float z) const;
		void setVec4(const std::string& name, const glm::vec4& value) const;
		void setVec4(const std::string& name, float x, float y, float z, float w) const;
		void setMat2(const std::string& name, const glm::mat2& matrix) const;
		void setMat3(const std::string& name, const glm::mat3& matrix) const;
		void setMat4(const std::string& name, glm::mat4& matrix) const;

		unsigned int ID();

		Shader() = delete;
		Shader(Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&& shader) noexcept;
		Shader(Shader&& shader) noexcept;

	private:

		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;

		unsigned int programID;
	};

}