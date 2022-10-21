#include "lcg_crack.h"

#include <iostream>
#include <array>

int main(int argc, char** argv) {
	if (argc != 5) {
		std::cerr << "Sequence input of four numbers is required!" << std::endl;
		return EXIT_FAILURE;
	}
	std::array<long, 4> given_sequence{};
	for (int i = 1; i < argc; ++i) {
		given_sequence[i - 1] = std::strtol(argv[i], nullptr, 10);
	}

	lcg::Predictor<long> pred(given_sequence, 65535);
	pred.print_to_console();
	return EXIT_SUCCESS;
}
