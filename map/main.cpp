#include <map>
#include <memory>

#include "avl.hpp"

int	main()
{
	// std::map<int, int>	m;

	ft::Avl<int, std::less<int>, std::allocator<int> > a;

	ft::Avl<int, std::less<int>, std::allocator<int> >::Node	node1(5);
	ft::Avl<int, std::less<int>, std::allocator<int> >::Node	node2(6);

	auto ptr1 = &node1;

	a._root->insert(ptr1, node2);
}