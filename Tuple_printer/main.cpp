#include <tuple>
#include <string>
#include "TuplePrinter.h"



int main() {

	std::tuple<int, char, bool, float, std::string> tupix{ 1, 'c', true, 3.45, "buenos_dias" };
	std::tuple<int*, std::tuple<int, char, bool, float, std::string>, std::string> tutupix{ nullptr, tupix, "bobom" };
	std::cout << tupix << std::endl;
	std::cout << tutupix << std::endl;
}
