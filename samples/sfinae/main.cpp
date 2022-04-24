// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

#include "../../type_traits/type_traits.hpp"

template<typename T>
void	foo(const typename ft::enable_if<ft::is_integral<T>::value, T>::type& n)
{
	std::cout << "itegral : " << n << std::endl;
}

template<typename T>
void	foo(const typename ft::enable_if<std::is_floating_point<T>::value, T>::type& n)
{
	std::cout << "floating_point : " << n << std::endl;
}

int main()
{
	foo<int>(15);
	foo<float>(3.6f);
	return 0;
}