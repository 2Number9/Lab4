#include <tuple>
#include <string>
#include "TuplePrinter.h"
#include "CsvParser.h"
#include <fstream>


int main(int argc, char**argv) {
	std::tuple<int, char, bool, float, std::string> tupix{ 1, 'c', true, 3.45, "buenos_dias" };
	std::tuple<int*, std::tuple<int, char, bool, float, std::string>, std::string> tutupix{ nullptr, tupix, "bobom" };

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
