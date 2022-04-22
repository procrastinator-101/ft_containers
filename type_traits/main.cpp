#include <iostream>
#include <iomanip>
#include "type_traits.hpp"

int	getFact();

int main()
{
	// std::cout << getFact();  // constexpr (no calculations on runtime)
	std::cout << std::boolalpha;

	std::cout << "is_integral:" << std::endl;
	std::cout << std::left;
	std::cout << std::setw(10) << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << ft::is_integral<float>::value << std::endl;

	std::cout << std::setw(10) << "////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::setw(10) << "char: " << ft::is_integral<const char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << ft::is_integral<const int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << ft::is_integral<const float>::value << std::endl;

	std::cout << std::setw(10) << "////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::setw(10) << "char: " << ft::is_integral<volatile char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << ft::is_integral<volatile int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << ft::is_integral<volatile float>::value << std::endl;

	std::cout << std::setw(10) << "////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::setw(10) << "char: " << ft::is_integral<const volatile char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << ft::is_integral<const volatile int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << ft::is_integral<const volatile float>::value << std::endl;

	std::cout << std::setw(10) << "////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::setw(10) << "is_integral:" << std::endl;
	std::cout << std::setw(10) << "char: " << std::is_integral<char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << std::is_integral<int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << std::is_integral<float>::value << std::endl;

	std::cout << std::setw(10) << "////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::setw(10) << "char: " << std::is_integral<const char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << std::is_integral<const int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << std::is_integral<const float>::value << std::endl;

	std::cout << std::setw(10) << "////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::setw(10) << "char: " << std::is_integral<volatile char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << std::is_integral<volatile int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << std::is_integral<volatile float>::value << std::endl;

	std::cout << std::setw(10) << "////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::setw(10) << "char: " << std::is_integral<const volatile char>::value << std::endl;
	std::cout << std::setw(10) << "int: " << std::is_integral<const volatile int>::value << std::endl;
	std::cout << std::setw(10) << "float: " << std::is_integral<const volatile float>::value << std::endl;
	return 0;
}