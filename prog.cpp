#include <iostream>
#include <string>

#include <GL/glew.h>

#include "prog.h"
#include "util.h"

Shad::Shad(std::string name, int stage) {
	std::string ext;
	GLenum type;
	switch (stage) {
		case Prog::VTX:
			ext = "vs";
			type = GL_VERTEX_SHADER;

			break;

		case Prog::FRAG:
			ext = "fs";
			type = GL_FRAGMENT_SHADER;

			break;

		default:
			std::cerr << "Error: Invalid enumeration for shader" << std::endl;

			break;
	}

	std::string path = "res/shad/" + name + "." + ext;

	std::string buff = util::rd(path);
	const char* src = buff.c_str();

	GLint succ;
	char errBuff[] = "";

	_id = glCreateShader(type);
	glShaderSource(_id, 1, &src, NULL);
	glCompileShader(_id);

	glGetShaderiv(_id, GL_COMPILE_STATUS, &succ);
	if (!succ) {
		glGetShaderInfoLog(_id, 512, NULL, errBuff);
		std::cout << "Error: " << std::endl;
		std::cout << errBuff << std::endl;
	}
}

Prog::Prog(std::string vtxName, std::string fragName) {
	Shad _vtx(vtxName, VTX);

	Shad _frag(fragName, FRAG);

	_id = glCreateProgram();
	glAttachShader(_id, _vtx._id);
	glAttachShader(_id, _frag._id);
	glLinkProgram(_id);
}

void Prog::use() {
	glUseProgram(_id);
}

void Prog::unUse() {
	glUseProgram(0);
}
