#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "math.h"
#include "disp.h"
#include "obj.h"

const unsigned int res[2] = {
	800,
	600
};

int main() {
	Disp disp("Cube", res[X], res[Y]);

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

	GLushort idc[3 * 2 * 3 * 2] = {
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

	Obj cube(vtc, idc, sizeof idc / sizeof *idc, "obj", "solid");

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		cube.matrix[Obj::MODEL] = glm::rotate(cube.matrix[Obj::MODEL], (GLfloat) 0.01, glm::vec3(1.0));

		disp.clear(1.0, 0.6, 0, 1);

		cube.prog.use();

		glUniformMatrix4fv(cube._uni[Obj::MODEL], 1, GL_FALSE, glm::value_ptr(cube.matrix[Obj::MODEL]));

		cube.draw();

		cube.prog.unUse();

		disp.update();
	}
}
