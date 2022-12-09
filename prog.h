#pragma once

#include "util.h"

class Shad {
	public:
		GLint _id;

		Shad(std::string name, int stage);
};

class Prog {
	public:
		GLint _id;

		Prog(std::string vtxName, std::string fragName);

		void use();

		void unUse();

		enum stage {
			VTX,
			FRAG
		};
};
