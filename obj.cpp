#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "prog.h"
#include "util.h"
#include "obj.h"

Obj::Obj(GLfloat* vtc, GLushort* idc, unsigned int noPrim, std::string nameVtx, std::string nameFrag) :
	prog(nameVtx, nameFrag),
	_noPrim(noPrim) {
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, noPrim * 3 * sizeof (GLfloat), vtc, GL_STATIC_DRAW);

		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, noPrim * 3 * sizeof (GLfloat), idc, GL_STATIC_DRAW);

		matrix[MODEL] = glm::mat4(1.0);
		matrix[VIEW] = glm::lookAt(glm::vec3(3.0, 3.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));
		matrix[PROJ] = glm::perspective(glm::radians(45.0), (double) 800 / 600, 0.1, 100.0);

		prog.use();

		GLint _attrPos = glGetAttribLocation(prog._id, "pos");
		glVertexAttribPointer(_attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
		glEnableVertexAttribArray(_attrPos);

		GLint uni[3];

		uni[MODEL] = glGetUniformLocation(prog._id, "model");
		uni[VIEW] = glGetUniformLocation(prog._id, "view");
		uni[PROJ] = glGetUniformLocation(prog._id, "proj");

		glUniformMatrix4fv(uni[MODEL], 1, GL_FALSE, glm::value_ptr(matrix[MODEL]));
		glUniformMatrix4fv(uni[VIEW], 1, GL_FALSE, glm::value_ptr(matrix[VIEW]));
		glUniformMatrix4fv(uni[PROJ], 1, GL_FALSE, glm::value_ptr(matrix[PROJ]));

		prog.unUse();
	}

Obj::~Obj() {
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ibo);
	glDeleteBuffers(1, &_vao);
}

void Obj::draw() {
	glBindVertexArray(_vao);
	prog.use();

	glDrawElements(GL_TRIANGLES, _noPrim, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	prog.unUse();
	glBindVertexArray(0);
}
