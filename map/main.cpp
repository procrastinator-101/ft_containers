// #include <map>
#include <memory>
#include <iostream>
#include <type_traits>

#include "avl.hpp"


int	main()
{
	// std::map<int, int>	m;

	ft::Avl<int, std::less<int>, std::allocator<int> > a;

	a.insert(15);
	a.insert(40);

	std::is_integral<int>::type l;

}