#pragma once

#include <glad/glad.h>
#include <string>

namespace Core {

	class Texture {

	public:
		Texture(const GLuint width, const GLuint height, const unsigned char* data, const unsigned int cannels = 4, const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);

		Texture() = delete;
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&& Texture);
		Texture(Texture&& Texture);
		~Texture();

		void bind() const;
	private:

		GLuint m_ID;
		GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;
	};
}
