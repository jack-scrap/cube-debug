#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"
#include "math.h"

unsigned int res[2] = {
	800,
	600
};

enum matrix {
	MODEL,
	VIEW,
	PROJ
};

int main() {
	Disp disp("asdf", res[X], res[Y]);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat vtc[2 * 2 * 2 * 3];
	int i = 0;
	for (int z = 0; z < 2; z++) {
		for (int y = 0; y < 2; y++) {
			for (int x = 0; x < 2; x++) {
				vtc[i] = x ? 1 : -1;
				vtc[i + 1] = y ? 1 : -1;
				vtc[i + 2] = z ? 1 : -1;

				i += 3;
			}
		}
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof vtc, vtc, GL_STATIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	GLuint idc[3 * 2 * 3 * 2] = {
		0, 1, 2,
		2, 1, 3,

		4, 5, 6,
		6, 5, 7,

		0, 4, 1,
		1, 4, 5,

		2, 6, 3,
		3, 6, 7,

		0, 4, 2,
		2, 4, 6,

		1, 5, 3,
		3, 5, 7
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof idc, idc, GL_STATIC_DRAW);

	glm::mat4 matrix[3];

	matrix[MODEL] = glm::mat4(1.0);
	matrix[VIEW] = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	matrix[PROJ] = glm::perspective(glm::radians(45.0), (double) res[X] / res[Y], 0.1, 100.0);

	Prog prog("shad", "shad");

	prog.use();

	GLint attrPos = glGetAttribLocation(prog._id, "pos");
	glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
	glEnableVertexAttribArray(attrPos);

	GLint uni[3];

	uni[MODEL] = glGetUniformLocation(prog._id, "model");
	uni[VIEW] = glGetUniformLocation(prog._id, "view");
	uni[PROJ] = glGetUniformLocation(prog._id, "proj");

	glUniformMatrix4fv(uni[MODEL], 1, GL_FALSE, glm::value_ptr(matrix[MODEL]));
	glUniformMatrix4fv(uni[VIEW], 1, GL_FALSE, glm::value_ptr(matrix[VIEW]));
	glUniformMatrix4fv(uni[PROJ], 1, GL_FALSE, glm::value_ptr(matrix[PROJ]));

	prog.unUse();

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0, 0, 0, 1);

		prog.use();

		glDrawElements(GL_TRIANGLES, sizeof idc / sizeof *idc, GL_UNSIGNED_INT, (GLvoid*) 0);

		prog.unUse();

		disp.update();
	}
}
