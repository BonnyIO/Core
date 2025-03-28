#include <glad/glad.h>
#include "../h/VertexBuf.hpp"

namespace Core {

	constexpr unsigned int SDT_to_componentCount(const SDT type) {

		switch (type) {

		case SDT::Float:
		case SDT::Int:
			return 1;

		case SDT::Float2:
		case SDT::Int2:
			return 2;

		case SDT::Float3:
		case SDT::Int3:
			return 3;

		case SDT::Float4:
		case SDT::Int4:
			return 4;
		}
	}

	constexpr size_t SDT_size(const SDT type) {

		switch (type) {

		case SDT::Float:
		case SDT::Float2:
		case SDT::Float3:
		case SDT::Float4:
			return sizeof(GLfloat) * SDT_to_componentCount(type);

		case SDT::Int:
		case SDT::Int2:
		case SDT::Int3:
		case SDT::Int4:
			return sizeof(GLint) * SDT_to_componentCount(type);
		}
	}

	constexpr unsigned int SDT_to_componentType(const SDT type) {

		switch (type) {

		case SDT::Float:
		case SDT::Float2:
		case SDT::Float3:
		case SDT::Float4:
			return GL_FLOAT;

		case SDT::Int:
		case SDT::Int2:
		case SDT::Int3:
		case SDT::Int4:
			return GL_INT;
		}
	}

	constexpr GLenum usage_to_GLenum(const VertexBuffer::EUsage usage) {

		switch (usage) {

		case VertexBuffer::EUsage::Static: return GL_STATIC_DRAW;
		case VertexBuffer::EUsage::Dynamic: return GL_DYNAMIC_DRAW;
		case VertexBuffer::EUsage::Stream: return GL_STREAM_DRAW;
		}

		return GL_STREAM_DRAW;
	}

	BufferElement::BufferElement(const SDT _type)
		: type(_type), componentType(SDT_to_componentType(_type)), componentCount(SDT_to_componentCount(_type)), size(SDT_size(_type)), offset(0) {


	}

	VertexBuffer::VertexBuffer(const void* data, const size_t size, BufferLayout bufferLayout, const EUsage usage) : m_layout(std::move(bufferLayout)) {

		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage_to_GLenum(usage));
	}

	VertexBuffer::~VertexBuffer() {

		glDeleteBuffers(1, &m_id);
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept {

		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
		return *this;
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept : m_id(vertexBuffer.m_id), m_layout(std::move(vertexBuffer.m_layout)) {

		vertexBuffer.m_id = 0;
	}

	void VertexBuffer::bind() const {

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::unbind() {

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}