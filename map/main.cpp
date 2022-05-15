// #include <map>
#include <memory>
#include <iostream>
#include <type_traits>

#include "avl.hpp"



int	main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	
	ft::Avl<int, std::less<int>, std::allocator<int> > a;
	if (argc == 2)
	{
		int n = atoi(argv[1]);
		srand(time(0));

		for (int i = 0; i < n; i++)
		{
			int val = std::rand() % n;
			std::cout << val << " ";
			a.insert(val);
		}
		std::cout << std::endl;
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			a.insert(std::atoi(argv[i]));
		}
	}
	a.show();
	char c = 0;
	int val = 0;
	while (c != 's')
	{
		std::cin >> val;
		std::cin >> c;
		a.erase(val);
		a.show();
	}
	return 0;
}