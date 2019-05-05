#pragma once

namespace opengl {

  class IndexBuffer {
	public:
	  IndexBuffer();
	  IndexBuffer(unsigned int *data, int amount);
	  ~IndexBuffer();

	  void load(unsigned int *data, int amount);

	  void bind() const;
	  void unbind() const;

	  inline int getCount() const { return m_Count; }

	private:
	  unsigned int m_BufferID;
	  int m_Count;
  };

}
