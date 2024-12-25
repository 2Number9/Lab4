#pragma once
#include <tuple>
#include <string>
#include <iostream>

template<size_t size>
struct dummy {}; 

template <typename Tuple, size_t size>
std::ostream& print_tuple(std::ostream& out, Tuple& t, dummy<size>) {
	out << std::get < std::tuple_size<Tuple>::value - size>(t) << ',';
	return print_tuple(out, t, dummy<size-1>());
}

template <typename Tuple>
std::ostream& print_tuple(std::ostream& out, Tuple& t, dummy<1>) {
	return out << std::get<std::tuple_size<Tuple>::value - 1>(t);
}


template <typename... Args>
std::ostream& operator<<(std::ostream& out, std::tuple<Args...>& t) {
	out << '(';
	return print_tuple(out, t, dummy<sizeof... (Args)>()) << ')';
}
