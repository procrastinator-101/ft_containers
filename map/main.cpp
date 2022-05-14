// #include <map>
#include <memory>
#include <iostream>
#include <type_traits>

#include "avl.hpp"



int	main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	int n = atoi(argv[1]);
	srand(time(0));
	ft::Avl<int, std::less<int>, std::allocator<int> > a;

	for (int i = 0; i < n; i++)
	{
		int val = std::rand() % n;
		std::cout << val << " ";
		a.insert(val);
	}
	std::cout << std::endl;

	a.show();
	// ft::Enclosing<int>	e;

	// std::cout << e << std::endl;

}