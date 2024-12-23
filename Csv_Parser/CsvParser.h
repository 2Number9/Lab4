#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>


namespace parser {
	class ParsingException : public std::runtime_error {
	public:
		ParsingException(std::string message) : std::runtime_error(""), message(message) {}
		const char* what() const noexcept override {
			return message.c_str();
		}
	private:
		std::string message;
	};

	bool is_string_element(std::string element) {
		int amount_of_blocks_of_symbols = 0;
		int previous_amount;
		while (element.length() > 0) {
		previous_amount	= amount_of_blocks_of_symbols;
			while (element.length() > 0) {
				if (element[0] == ' ') {
					element.erase(0, 1);
				}
				else
					break;
			}
			previous_amount = amount_of_blocks_of_symbols;
			while (element.length() > 0) {
				if (element[0] != ' ') {
					amount_of_blocks_of_symbols++;
					element.erase(0, 1);
				}
				else
					break;
			}
			if (amount_of_blocks_of_symbols > previous_amount)
				amount_of_blocks_of_symbols = previous_amount + 1;
		}
		if (amount_of_blocks_of_symbols > 1)
			return true;
		else
			return false;
	}

	std::string erasing_last_spaces_for_number(std::string str) {
		while ((str.length() > 0) && (str[str.length()-1] == ' '))
			str.erase(str.length()-1, 1);
		//std::cout << "str == " << str << " str.length() == " << str.length() << std::endl;
		return str;
	}

	bool is_numeric(std::string str) {
		for (int i = 0; i < str.length(); i++) {
			if ((str[i] != '-') && (str[i] != '+') && ((str[i] < '0') || (str[i] > '9')) && (str[i] != '.') && (str[i] != ' '))
				return false;
		}
		return true;
	}

	int is_bool(std::string str) {
		if ((str.find("false") != std::string::npos) || (str.find("False") != std::string::npos))
			return 2;
		else
			if ((str.find("true") != std::string::npos) || (str.find("True") != std::string::npos))
				return 1;
			else 
				return 0;
	}

	template<size_t I, typename... Args>
	auto ParseElement(std::istringstream& element, std::tuple<Args...> &tupix) { //
		std::string current_element;
		std::getline(element, current_element, ',');
		if (!(is_string_element(current_element)))
			if (is_numeric(current_element))
				current_element = erasing_last_spaces_for_number(current_element);
		//std::cout << "current_elementeee == " << current_element << " current_element.length() == " << current_element.length() << std::endl;
		
		try {								   //сделать так, чтобы пробелы тоже считывались

			//std::stringstream ss(current_element); //позволяет преобразовывать строки в различные типы данных
			
												  //как числа, даже если они как числа
			int bitch = is_bool(current_element);
			if ((!(is_string_element(current_element))) && ((is_numeric(current_element)) || (bitch > 0))) {
				if (bitch == 1) {
					current_element = "1";
					//std::cout << "huya: " << current_element << std::endl;
				}
				else
					if (bitch == 2) {
						current_element = "0";
						//std::cout << "nihuya: " << current_element << std::endl;
					}
				std::stringstream ss(current_element);
				//std::cout << "ss.str() == " << ss.str() << " ss.str().length() == " << ss.str().length() << std::endl;
				//std::cout << "std::get<I>(tupix) == " << std::get<I>(tupix) << std::endl;
				
				if (!(ss >> std::get<I>(tupix)))
					throw std::invalid_argument("Wrong element");
			}
			else {
				//std::stringstream cc("");
				//std::cout << "cc.str() == " << cc.str() << std::endl;
				//if (!(cc >> std::get<I>(tupix))) {
					//std::cout << "";
				//}
				while (current_element.length() > 0) {
					std::get<I>(tupix) += current_element[0];
					current_element.erase(0, 1);
				}
				//std::cout << "babidjon.str() == " << std::get<I>(tupix) << std::endl;
				//if (!(ss >> std::get<I>(tupix)))
					//throw std::invalid_argument("Wrong element");
				//std::cout << "after bobij: " << std::get<I>(tupix) << std::endl;
			}



			/*if ((!(is_numeric(current_element))) || (is_string_element(current_element))) {
				
				//std::cout << "zalupa happend with current_element: " << current_element << std::endl;
					//throw std::invalid_argument("Wrong element eblan");
				char zalupa;
				//while ((current_element.length() > 0) && (current_element[0] != ' ')) { //убираем вошедшую строку
					//std::get<I>(tupix) += current_element[0];
					//current_element.erase(0, 1);
						//std::cout << "editing: " << current_element << std::endl;
									//std::get<I>(tupix) += 'c';
				std::string huijopa = "";
				std::stringstream chlen(huijopa);
				chlen >> std::get<I>(tupix);
				std::cout << "chlen.std::get<I>(tupix) == " << std::get<I>(tupix) << std::endl;
				while (true) {
					while ((current_element.length() > 0) && (current_element[0] != ' ')) {
						std::get<I>(tupix) += current_element[0];
						current_element.erase(0, 1);
						std::cout << "editing: " << current_element << std::endl;
					}
					//std::cout << "jopa.ss.str() == " << ss.str() << std::endl;
					while ((current_element.length() > 0) && (current_element[0] == ' ')) {
						//std::cout << "jopa: " << current_element << "current_element[0] == " << current_element[0] << std::endl;
						zalupa = current_element[0];
						current_element.erase(0, 1);
						std::get<I>(tupix) += zalupa;
					}
					if (current_element.length() == 0)
						break;
					std::stringstream ss(current_element);

				}
			}
			else {
				std::cout << "std::get<I>(tupix) == " << std::get<I>(tupix) << std::endl;
				if (!(ss >> std::get<I>(tupix)))
					throw std::invalid_argument("Wrong element");
			}*/
		}
		catch (const std::invalid_argument& except) {
			throw I + 1;
		}
		if constexpr (I + 1 < sizeof... (Args))
			ParseElement<I + 1>(element, tupix);
	}

	template<typename... Args>
	std::ifstream& ParseLine(std::ifstream& in, std::tuple<Args...>& tupix, size_t line) {
		std::string str;
		std::getline(in, str);
		if (str.empty())
			return in;
		std::istringstream element(str);
		try {
			//std::cout << "element == " << str << std::endl;
			parser::ParseElement<0>(element, tupix);
		}
		catch (const size_t column) {
			throw ParsingException("Parsing Error in " + std::to_string(line + 1) + "line, " + std::to_string(column + 1) + "column");
		}
		return in;
	}

	template<typename... Args>
	class CsvParser {

	public:
		class Iterator {
		public:

			explicit Iterator(std::ifstream* in) : in(in) {
				if (in == nullptr) {
					position = -1;
				}
				else {
					parser::ParseLine(*in, tupix, position);
				}
			}

			~Iterator() = default;

			bool operator==(const Iterator& b) {
				if (in != b.in) {
					return false;
				}
				else {
					if (position != b.position)
						return false;
					else
						return true;
				}
			}

			bool operator!=(const Iterator& b) {
				if (in != b.in) {
					return true;
				}
				else
					return (position != b.position);
			}

			Iterator operator++() {
				if (in == nullptr) {
					return *this;
				}
				//std::cout << "tupix: " << tupix << std::endl;
				std::tuple<std::string, std::string, int, float, bool> billy{ "", "", 0, 0, false };
				tupix = billy;
				parser::ParseLine(*in, tupix, position);
				if (in->eof()) {
					in = nullptr;
					std::cout << tupix << std::endl;
					position = -1;
					return *this;
				}
				
				position++;
				return *this;
			}

			std::tuple<Args...> operator*() {
				return tupix;
			}


		private:
			std::ifstream* in;
			std::tuple<Args...> tupix;
			size_t position = 0;
		};

		CsvParser(std::ifstream& input, size_t skip_count) {
			if ((input.peek() == EOF) || (input.peek() == '\n'))
				throw std::invalid_argument("Empty file buddy");
			std::string str;
			for (int i = 0; i < skip_count; i++) {
				std::getline(input, str);
			}
			in = &input;
		}

		Iterator begin() {
			return Iterator(in);
		}

		Iterator end() {
			return Iterator(nullptr);
		}

	private:
		std::ifstream *in;

	};

}