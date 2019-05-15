#include "model.h"
#include "GL/glew.h"

namespace graphics {

  Model::Model(const Mesh &mesh) {
	addData(mesh);
  }

  Model::~Model() {
	deleteData();
  }

  Model::Model(Model &&other) : m_vao(other.m_vao), m_vboCount(other.m_vboCount), 
	m_indicesCount(other.m_indicesCount), m_buffers(std::move(other.m_buffers)) {

	  other.m_vao             = 0;
	  other.m_vboCount        = 0;
	  other.m_indicesCount    = 0;
	}

  Model& Model::operator=(Model&& other) {
	m_vao = other.m_vao;
	m_vboCount = other.m_vboCount;
	m_indicesCount = other.m_indicesCount;
	m_buffers = std::move(other.m_buffers);

	other.m_vao             = 0;
	other.m_vboCount        = 0;
	other.m_indicesCount    = 0;

	return *this;
  }


  void Model::bindVAO() const {
	glBindVertexArray(m_vao);
  }

  // TODO: Should add Normals too.
  void Model::addData(const Mesh& mesh) {
	if (m_vao != 0)
	  deleteData();

	m_indicesCount = mesh.indices.size();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addEBO(mesh.indices);
  }

  void Model::addVBO(int dimensions, const std::vector<float> &data) {
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(m_vboCount, dimensions, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

	glEnableVertexAttribArray(m_vboCount++);

	m_buffers.push_back(vbo);
  }

  void Model::addEBO(const std::vector<unsigned int> &indices) {
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
  }

  void Model::deleteData() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(m_buffers.size(), m_buffers.data());

	m_buffers.clear();

	m_vboCount = 0;
	m_vao = 0;
	m_indicesCount = 0;
  }

  int Model::getIndicesCount() const {
	return m_indicesCount;
  }

}
