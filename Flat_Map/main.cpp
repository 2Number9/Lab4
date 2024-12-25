#include "FlatMap.h"

int main() {
	
	FlatMap<std::string, float> flat_map1;
	FlatMap<bool, char> flat_map2;
	
	flat_map1["NSU"] = 16.166;
	flat_map1["University"] = 788.888;
	flat_map1["FIT"] = -0.086;
	flat_map1["23207"] = 232.323;
	
	for (const auto& iter : flat_map1) {
		std::cout << '(' << iter.key << ',' << iter.value << ')' << std::endl;
	}

	std::cout << "*****" << std::endl;

	flat_map2[false] = 'o';
	flat_map2[true] = 'k';
	flat_map2[true] = 'n';

	for (auto& iter : flat_map2) {
		std::cout << '(' << iter.key << ',' << iter.value << ')' << std::endl;
	}
}
