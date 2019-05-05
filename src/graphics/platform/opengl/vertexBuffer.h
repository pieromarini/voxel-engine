#pragma once

namespace opengl {

  class VertexBuffer {
	private:
	  unsigned int m_BufferID;
	  unsigned int m_ComponentCount;
	public:
	  VertexBuffer();
	  VertexBuffer(float *data, int amount, unsigned int componentCount);
	  ~VertexBuffer();

	  void load(float *data, int amount, unsigned int componentCount);

	  void bind() const;
	  void unbind() const;

	  inline unsigned int getComponentCount() const { return m_ComponentCount; }
  };

}
