#include "../avl.hpp"

#include <map>
#include <memory>
#include <utility>

static void	verbose(int n)
{
	std::map<int, int>	m;

	// for (int i = 0; i < 2; i++)
	// 	m.insert(std::make_pair(i, i));
	std::map<int, int>::iterator	it = m.end();

	(void)n;
	// ++it;
	// --it;
	// --it;
	std::cout << &(*it) << std::endl;
	// m.insert(std::make_pair(11, 12));
	std::cout << it->first << std::endl;
}

void	testAvlIterator(int n)
{
	std::map<int, int>	m;
	ft::Avl<int, std::less<int>, std::allocator<int>>	tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(i);
		m.insert(std::make_pair(i, i));
	}
	ft::Avl<int, std::less<int>, std::allocator<int>>::iterator	it = tree.begin();
}