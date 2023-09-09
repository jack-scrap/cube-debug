#include "mesh.h"

Mesh::Mesh(GLfloat* vtc, GLushort* idc, unsigned int noPrim) {
	noPrim = noPrim;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _noPrim * 3 * sizeof (GLfloat), vtc, GL_STATIC_DRAW);

	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, noPrim * sizeof (GLushort), idc, GL_STATIC_DRAW);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ibo);
}
