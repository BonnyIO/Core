#include "../h/Texture.hpp"

namespace Core {

	Texture::Texture(const GLuint width, const GLuint height, const unsigned char* data, const unsigned int cannels, const GLenum filter, const GLenum wrapMode) : m_width(width), m_height(height) {

		switch (cannels) {

		case 4:
			m_mode = GL_RGBA;
			break;

		case 3:
			m_mode = GL_RGB;
			break;

		default:
			m_mode = GL_RGBA;
			break;
		}

		glGenTextures(1, &m_ID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture& Texture::operator=(Texture&& Texture) {

		glDeleteTextures(1, &m_ID);
		m_ID = Texture.m_ID;
		Texture.m_ID = 0;
		m_mode = Texture.m_mode;
		m_width = Texture.m_width;
		m_height = Texture.m_height;
		return *this;
	}

	Texture::Texture(Texture&& Texture) {

		m_ID = Texture.m_ID;
		Texture.m_ID = 0;
		m_mode = Texture.m_mode;
		m_width = Texture.m_width;
		m_height = Texture.m_height;
	}

	Texture::~Texture() {

		glDeleteTextures(1, &m_ID);
	}

	void Texture::bind() const {

		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}