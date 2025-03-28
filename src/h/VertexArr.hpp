#pragma once

#include "VertexBuf.hpp"
#include "IndexBuf.hpp"

namespace Core {

	class VertexArray {

	public:

		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&& vertexArray) noexcept;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&& vertexArray) noexcept;

		void addVertexBuffer(const VertexBuffer& vertexBuffer);
		void setIndexBuffer(const IndexBuffer& indexBuffer);
		void bind() const;
		static void unbind();
		size_t getIndex() const { return m_index; }

	private:

		unsigned int m_id = 0;
		unsigned int m_elementsCount = 0;
		size_t m_index = 0;
	};
}