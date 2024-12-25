#include "CsvParser.h"
#include "TuplePrinter.h"


int main(int argc, char** argv) {
	try {
		if (argc < 3) {
			std::ifstream in(argv[1]);
			parser::CsvParser<std::string, std::string, int, float, bool> parser(in, 0);
			std::cout << argv[1] << std::endl;
			for (auto& rs : parser) {
				std::cout << rs << std::endl;
			}
		}
	}
	catch (const std::exception& except) {
		std::cerr << except.what() << std::endl;
	}

}
