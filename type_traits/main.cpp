#include <iostream>
#include <iomanip>
#include "type_traits.hpp"

#include "../vector/vectorIterator.hpp"

int	getFact();

void	testIsIntegral()
{
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
}

void	testIsIterator()
{
	std::cout << std::boolalpha;

	std::cout << "is_forward_iterator:" << std::endl;
	std::cout << std::left;
	std::cout << std::setw(30) << "char* : " << ft::is_forward_iterator<char *>::value << std::endl;
	std::cout << std::setw(30) << "char* : " << std::__is_forward_iterator<char *>::value << std::endl;
	std::cout << "======================================================================================" << std::endl;
	std::cout << "is_random_access_iterator:" << std::endl;
	std::cout << "======================================================================================" << std::endl;
	std::cout << std::setw(30) << "char* : " << ft::is_random_access_iterator<char *>::value << std::endl;
	std::cout << std::setw(30) << "char* : " << std::__is_random_access_iterator<char *>::value << std::endl;
	std::cout << "======================================================================================" << std::endl;
	std::cout << std::setw(30) << "ft::vectorIterator<int> : " << ft::is_random_access_iterator<ft::vectorIterator<int> >::value << std::endl;
	std::cout << std::setw(30) << "ft::vectorIterator<int> : " << std::__is_random_access_iterator<ft::vectorIterator<int> >::value << std::endl;
	std::cout << "======================================================================================" << std::endl;
	// std::cout << std::setw(30) << "char : " << ft::is_random_access_iterator<char>::value << std::endl;
	// std::cout << std::setw(30) << "char: " << std::__is_random_access_iterator<char>::value << std::endl;
}

void	testIsSame()
{
	std::cout << std::boolalpha;

	typedef int mint;
	std::cout << "is_same:" << std::endl;
	std::cout << std::left;
	std::cout << std::setw(10) << "char == char: " << ft::is_same<char, char>::value << std::endl;
	std::cout << std::setw(10) << "int * == char *: " << ft::is_same<int *, char *>::value << std::endl;
	std::cout << std::setw(10) << "void == void * " << ft::is_same<void, void*>::value << std::endl;
	std::cout << std::setw(10) << "mint == int: " << ft::is_same<mint, int>::value << std::endl;
}

int main()
{
	testIsIterator();
	// testIsSame();
	return 0;
}