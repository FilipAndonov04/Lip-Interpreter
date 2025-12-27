#include "Interpreter/Interpreter.h"
#include "Interpreter/Init.h"

#include "Utils/StringUtils.h"

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, const char** argv) {
	if (argc > 2) {
		std::cerr << "invalid usage, correct format:\n" << argv[0] << " [filename]\n";
	}

	Interpreter inter = initInterpreter();
	if (argc == 2) {
		std::ifstream ifs(argv[1]);
		if (!ifs.is_open()) {
			std::cerr << "file does not open\n";
			return EXIT_FAILURE;
		}

		std::string line;
		while (std::getline(ifs, line)) {
			inter.interpret(line);
		}
	}

	// load some prewritten functions
	bool hasCacheFile = true;
	const char* cacheFuncFile = "functions.txt";
	if (hasCacheFile) {
		std::ifstream ifs(cacheFuncFile);
		if (!ifs.is_open()) {
			std::cerr << "cached file does not open\n";
		}

		std::string line;
		while (std::getline(ifs, line)) {
			inter.interpret(line);
		}
	}

	while (true) {
		std::cout << "input command: " << Utils::GREEN;
		std::string line;
		std::getline(std::cin, line);
		std::cout << Utils::DEFAULT;

		if (line == "quit") {
			break;
		}

		inter.interpret(line);
	}
}