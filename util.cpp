#include <fstream>
#include <iostream>

#include "util.h"

std::string util::rd(std::string fName) {
	std::ifstream in;
	in.open("./" + fName);

	std::string total;
	for (
		std::string l;
		std::getline(in, l);
	) {
		total += l + "\n";
	}

	in.close();

	return total;
}
