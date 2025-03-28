#pragma once

#include <vector>

namespace Core {

	enum class SDT {

		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4
	};

	struct BufferElement {

		SDT type;
		uint32_t componentType;
		size_t componentCount;
		size_t size;
		size_t offset;

		BufferElement(const SDT type);
	};

	class BufferLayout {

	public:

		BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(std::move(elements)) {

			size_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements) {

				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
		}

		const std::vector<BufferElement>& getElements() const { return m_elements; }
		size_t getStride() const { return m_stride; }

	private:

		std::vector<BufferElement> m_elements;
		size_t m_stride = 0;
	};

	class VertexBuffer {

	public:

		enum class EUsage {

			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void* data, const size_t size, BufferLayout bufferLayout, const EUsage usage = VertexBuffer::EUsage::Static);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;

		void bind() const;
		static void unbind();

		const BufferLayout& getLayout() const { return m_layout; }

	private:

		unsigned int m_id = 0;
		BufferLayout m_layout;
	};
}