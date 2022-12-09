#include <iostream>
#include <string>

#include <GL/glew.h>

#include "prog.h"
#include "util.h"

Shad::Shad(std::string name, int stage) {
	std::string ext;
	GLenum type;

	switch (stage) {
		case 0:
			ext = "fs";
			type = GL_FRAGMENT_SHADER;

			break;

		case 1:
			ext = "vs";
			type = GL_VERTEX_SHADER;

			break;
	}

	std::string path = name + "." + ext;

	std::string txt = util::rd(path);
	const char* src = txt.c_str();

	GLint succ;
	char buff[] = "";

	_id = glCreateShader(type);
	glShaderSource(_id, 1, &src, NULL);
	glCompileShader(_id);

	glGetShaderiv(_id, GL_COMPILE_STATUS, &succ);
	if (!succ) {
		glGetShaderInfoLog(_id, 512, NULL, buff);
		std::cout << "Error: " << std::endl;
		std::cout << buff << std::endl;
	}
}

Prog::Prog(std::string vtx, std::string frag) {
	Shad _vtx(vtx, 1);

	Shad _frag(frag, 0);

	_id = glCreateProgram();
	glAttachShader(_id, _vtx._id);
	glAttachShader(_id, _frag._id);
	glLinkProgram(_id);

	glBindFragDataLocation(_id, 0, "col");
}

void Prog::use() {
	glUseProgram(_id);
}

void Prog::unUse() {
	glUseProgram(0);
}
