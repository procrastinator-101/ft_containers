#include <iostream>     // std::cout
#include <typeinfo>     // typeid

#include "iterator_traits.hpp"

int main()
{
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator";
	return 0;
}