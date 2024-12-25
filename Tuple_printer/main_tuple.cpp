#include "TuplePrinter.h"



int main() {

	std::tuple<int, char, bool, float, std::string> tuple_1{ 1, 'c', true, 3.45, "buenos_dias" };
	std::tuple<int*, std::tuple<int, char, bool, float, std::string>, std::string> tuple_2{ nullptr, tuple_1, "JohnyNapalm" };
	std::cout << tuple_1 << std::endl;
	std::cout << tuple_2 << std::endl;
}
