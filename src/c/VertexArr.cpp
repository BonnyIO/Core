#include <glad/glad.h>
#include "../h/VertexArr.hpp"

namespace Core {

	VertexArray::VertexArray() {

		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray() {

		glDeleteVertexArrays(1, &m_id);
	}

	VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept {

		m_id = vertexArray.m_id;
		m_elementsCount = vertexArray.m_elementsCount;
		vertexArray.m_id = 0;
		vertexArray.m_elementsCount = 0;
		return *this;
	}

	VertexArray::VertexArray(VertexArray&& vertexArray) noexcept : m_id(vertexArray.m_id), m_elementsCount(vertexArray.m_elementsCount) {


		vertexArray.m_id = 0;
		vertexArray.m_elementsCount = 0;
	}

	void VertexArray::addVertexBuffer(const VertexBuffer& vertexBuffer) {

		bind();
		vertexBuffer.bind();

		for (const BufferElement& currentElement : vertexBuffer.getLayout().getElements()) {

			glEnableVertexAttribArray(m_elementsCount);

			glVertexAttribPointer(m_elementsCount, static_cast<GLint>(currentElement.componentCount), currentElement.componentType, GL_FALSE,
				static_cast<GLsizei>(vertexBuffer.getLayout().getStride()), reinterpret_cast<const void*>(currentElement.offset));

			++m_elementsCount;
		}
	}

	void VertexArray::setIndexBuffer(const IndexBuffer& indexBuffer) {

		bind();
		indexBuffer.bind();
		m_index = indexBuffer.getCount();
	}

	void VertexArray::bind() const {

		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() {

		glBindVertexArray(0);
	}


}