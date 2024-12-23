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

	bool detecting_strings_with_spaces(std::string element) {
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
		while ((str.length() > 0) && (str[0] == ' '))
			str.erase(0, 1);
		while ((str.length() > 0) && (str[str.length() - 1] == ' '))
			str.erase(str.length() - 1, 1);
	
		if ((str == "false") || (str == "False"))
			return 2;
		else
			if ((str == "true") || (str == "True"))
				return 1;
			else 
				return 0;
	}

	int amount_of_digits(int paramether) {
		int result = 0;
		while (paramether > 9) {
			result++;
			paramether /= 10;
		}
		return result;
	}

	template<size_t I, typename... Args>
	auto ParseElement(std::istringstream& element, std::tuple<Args...> &tupix) {
		std::string current_element;
		std::getline(element, current_element, ',');
		if (!(detecting_strings_with_spaces(current_element)))
			if (is_numeric(current_element))
				current_element = erasing_last_spaces_for_number(current_element);
		
		try {

			
			int kinda_bool = is_bool(current_element);
			if ((!(detecting_strings_with_spaces(current_element))) && ((is_numeric(current_element)) || (kinda_bool > 0))) {
				if (kinda_bool == 1) {
					current_element = "1";
				}
				else
					if (kinda_bool == 2) {
						current_element = "0";
					}
				std::stringstream ss(current_element);
				if (!(ss >> std::get<I>(tupix)))
					throw std::invalid_argument("Wrong element");
				ss.tellg();
				if ((static_cast<size_t> (ss.str().length()) != current_element.length()) || (!(ss.fail())))
					throw std::invalid_argument("Wrong element");

			}
			else {

				std::stringstream ss(current_element);
				if (!(ss >> std::get<I>(tupix)))
					throw std::invalid_argument("Wrong element");
				else {
					if (!(ss.eof())) {
						for (int i = ss.tellg(); i < current_element.length(); i++)
							std::get<I>(tupix) += current_element[i];
					}
				}

				
			}



			
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
			parser::ParseElement<0>(element, tupix);
		}
		catch (const size_t column) {
			throw ParsingException("Parsing Error in " + std::to_string(line+1) + "line, " + std::to_string(column) + "column");
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
				position++;
				parser::ParseLine(*in, tupix, position);
				if (in->eof()) {
					in = nullptr;
					std::cout << tupix << std::endl;
					position = -1;
					return *this;
				}
				
			
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
				throw std::invalid_argument("Empty file");
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