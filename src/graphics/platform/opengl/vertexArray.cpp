#include "vertexArray.h"

namespace opengl {

  VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_VertexArrayID);
  }

  VertexArray::~VertexArray() {
	unbind();
	glDeleteVertexArrays(1, &m_VertexArrayID);
  }

  void VertexArray::addBuffer(VertexBuffer *buffer, int index) {
	bind();

	buffer->bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
	buffer->unbind();

	unbind();

	m_Buffers.push_back(buffer);
  }

  void VertexArray::addIndexBuffer(IndexBuffer *buffer) {
	m_IndexBuffers.push_back(buffer);
  }

  void VertexArray::bind() const {
	glBindVertexArray(m_VertexArrayID);
	for (auto &b : m_Buffers)
	  b->bind();
	for (auto &ib : m_IndexBuffers)
	  ib->bind();
  }

  void VertexArray::unbind() const {
	glBindVertexArray(0);
	for (auto &b : m_Buffers)
	  b->unbind();
	for (auto &ib : m_IndexBuffers)
	  ib->unbind();
  }

}
