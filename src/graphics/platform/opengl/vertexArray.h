#pragma once

#include "../../../includes.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"

namespace opengl {

  class VertexArray {
	private:
	  unsigned int m_VertexArrayID;
	  std::vector<VertexBuffer*> m_Buffers;
	  std::vector<IndexBuffer*> m_IndexBuffers;

	public:
	  VertexArray();
	  ~VertexArray();

	  void addBuffer(VertexBuffer *buffer, int index);
	  void addIndexBuffer(IndexBuffer *buffer);

	  void bind() const;
	  void unbind() const;
  };

}
