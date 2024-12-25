#include "CsvParser.h"
#include "TuplePrinter.h"


int main(int argc, char** argv) {
	try {
		if (argc < 3) { //сделать run_all_tests()
			std::ifstream in(argv[1]); //поток входа (чтения)
			if (!(in.is_open()))
				throw parser::ParsingException("No Input File");
			parser::CsvParser<std::string, std::string, int, float, bool> parser(in, 0);
			//parser::CsvParser<bool, float, std::string> parser(in, 0);
			std::cout << argv[1] << std::endl;
			for (auto& rs : parser) {
				std::cout << rs << std::endl;
			}
		}
	}
	catch (const parser::ParsingException& except) {
		std::cerr << except.what() << std::endl;
	}

}
