#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "mesh.h"

namespace graphics {

  class Model {
	public:
	  Model() = default;
	  Model(const Mesh &mesh);
	  ~Model();

	  Model(Model &&other);
	  Model& operator=(Model &&other);

	  void addData(const Mesh &mesh);

	  void deleteData();

	  void addVBO(int dimensions, const std::vector<float> &data);
	  void bindVAO() const;

	  int getIndicesCount() const;

	private:
	  void addEBO(const std::vector<unsigned int> &indices);

	  unsigned int m_vao = 0;
	  int m_vboCount = 0;
	  int m_indicesCount = 0;
	  std::vector<unsigned int> m_buffers;
  };

}

#endif
