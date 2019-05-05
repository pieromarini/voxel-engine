#include "../../../includes.h"
#include "vertexBuffer.h"

namespace opengl {

  VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &m_BufferID);
  }

  VertexBuffer::VertexBuffer(float *data, int amount, unsigned int componentCount) {
	glGenBuffers(1, &m_BufferID);
	load(data, amount, componentCount);
  }

  VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_BufferID);
  }

  void VertexBuffer::load(float *data, int amount, unsigned int componentCount) {
	m_ComponentCount = componentCount;
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);
  }

  void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
  }

  void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

}
