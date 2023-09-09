#pragma one

#include <GL/glew.h>

class Mesh {
	public:
		unsigned int _noPrim;

		GLuint _vao;

		GLuint _vbo;

		GLuint _ibo;

		Mesh(GLfloat* vtc, GLushort* idc, unsigned int noPrim);

		~Mesh();
};
