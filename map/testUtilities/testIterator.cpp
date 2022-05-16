#include "../avl.hpp"

#include <map>
#include <memory>
#include <utility>

// static void	verbose(int n)
// {
// 	std::map<int, int>	m;

// 	// for (int i = 0; i < 2; i++)
// 	// 	m.insert(std::make_pair(i, i));
// 	std::map<int, int>::iterator	it = m.end();

// 	(void)n;
// 	// ++it;
// 	// --it;
// 	// --it;
// 	std::cout << &(*it) << std::endl;
// 	// m.insert(std::make_pair(11, 12));
// 	std::cout << it->first << std::endl;
// }

void	testAvlIterator(int n)
{
	std::map<int, int>	m;
	ft::Avl<int, std::less<int>, std::allocator<int> >	tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(i);
		m.insert(std::make_pair(i, i));
	}
	tree.show();
	std::cout << "ok" << std::endl;
	ft::Avl<int, std::less<int>, std::allocator<int> >::iterator	it = tree.begin();
	std::cout << "ok !" << std::endl;
	std::cout << *it << std::endl;
	std::cout << "ok End" << std::endl;
	for (it = tree.begin(); it != tree.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	// ft::Avl<int, std::less<int>, std::allocator<int> >::iterator	ite = tree.end();

	// tree.erase(11);
	// // ++ite;
	// --ite;
	// std::cout << *ite << std::endl;

	std::map<int, int>::iterator	mite = m.end();

	m.erase(11);
	// ++ite;
	--mite;
	std::cout << mite->first << std::endl;

}