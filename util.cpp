#include <fstream>
#include <iostream>

#include "util.h"

std::string util::rd(std::string fName) {
	std::ifstream in;
	in.open("./" + fName);

	std::string str;
	for (std::string l; std::getline(in, l);) {
		str += l + "\n";
	}

	in.close();

	return str;
}
