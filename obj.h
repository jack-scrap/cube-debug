#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "prog.h"

class Obj {
	private:
		unsigned int _noPrim;

		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;

		GLint _attrPos;

	public:
		Obj(GLfloat* vtc, GLushort* idc, unsigned int noPrim, std::string nameVtx, std::string nameFrag);

		~Obj();

		void draw();

		glm::mat4 matrix[3];

		Prog prog;

		GLint _uni[3];

		typedef enum {
			MODEL,
			VIEW,
			PROJ
		} uni_t;
};
