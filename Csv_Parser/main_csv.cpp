#include "CsvParser.h"
#include "TuplePrinter.h"

struct noop {
	void operator()(...) const {}
};


int main(int argc, char** argv) {
	try {
		if (argc < 3) {
			
			std::ifstream in(argv[1]); //поток входа (чтения)
			if (!(in.is_open()))
				throw parser::ParsingException("No Input File");
			parser::CsvParser<std::string, std::string, int, float, bool> parser(in, 0);
			
			//parser::CsvParser<int, char, std::string> parser(std::cin, 0);

			//parser::CsvParser<bool, float, std::string> parser(in, 0);

			std::cout << argv[1] << std::endl;
			for (auto& rs : parser) {
				std::cout << rs << std::endl;
			}
		}
		else
			throw parser::ParsingException("Wrong amount of Input Files");
	}
	catch (const parser::ParsingException& except) {
		std::cerr << except.what() << std::endl;
	}

}
