#include "../h/Shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Core {

	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) {

		GLuint vertexShaderID;

		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER Compile time error!" << std::endl;
			return;
		}

		GLuint fragmentShaderID;

		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER Compile time error!" << std::endl;
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER Link time error;\n" << infoLog << std::endl;
		}

		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool Shader::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, NULL);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER Compile time error;\n" << infoLog << std::endl;
			return false;
		}

		return true;
	}

	Shader::~Shader() {
		glDeleteProgram(m_ID);
	}

	void Shader::use() const {
		glUseProgram(m_ID);
	}

	unsigned int Shader::ID() {

		return m_ID;
	}

	Shader& Shader::operator=(Shader&& shader) noexcept {
		glDeleteProgram(m_ID);
		m_ID = shader.m_ID;
		m_isCompiled = shader.m_isCompiled;

		m_ID = shader.m_ID = 0;
		m_isCompiled = shader.m_isCompiled = false;
		return *this;
	}

	Shader::Shader(Shader&& shader) noexcept {
		m_ID = shader.m_ID;
		m_isCompiled = shader.m_isCompiled;

		m_ID = shader.m_ID = 0;
		m_isCompiled = shader.m_isCompiled = false;
	}

	void Shader::setBool(const std::string& name, bool value) const {

		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, const GLint value) const {

		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value) const {

		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::setVec2(const std::string& name, const glm::vec2& value) const {

		glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec2(const std::string& name, float x, float y) const {

		glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
	}

	void Shader::setVec3(const std::string& name, const glm::vec3& value) const {

		glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec3(const std::string& name, float x, float y, float z) const {

		glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
	}

	void Shader::setVec4(const std::string& name, const glm::vec4& value) const {

		glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {

		glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
	}

	void Shader::setMat2(const std::string& name, const glm::mat2& matrix) const {

		glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setMat3(const std::string& name, const glm::mat3& matrix) const {

		glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setMat4(const std::string& name, glm::mat4& matrix) const {

		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

}