#include "../avl.hpp"
#include "../../vector/testUtilities/display.hpp"

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

template<typename T>
void	checkContent(std::map<T, T>& m, ft::Avl<T, std::less<T>, std::allocator<T> >& tree)
{
	typename std::map<T, T>::reverse_iterator	mit = m.rbegin();
	typename ft::Avl<T, std::less<T>, std::allocator<T> >::reverse_iterator	it = tree.rbegin();
	displayHeader("checkContent");
	while (it != tree.rend())
	{
		std::cout << "++++" << std::endl;
		if (mit->first != *it)
			std::cout << "RevIter KO !!!!" << std::endl;
		std::cout << *it << " ";
		++it;
		++mit;
	}
	std::cout << std::endl;
	displayHeader("checkContent End");
}

template<typename T>
void	testAvlRevIter(std::map<T, T>& m, ft::Avl<T, std::less<T>, std::allocator<T> >& tree)
{
	displayHeader("testAvlRevIter");
	checkContent(m, tree);
	if (!m.empty())
	{
		typename std::map<T, T>::reverse_iterator	mit = m.rend();
		typename ft::Avl<T, std::less<T>, std::allocator<T> >::reverse_iterator	it = tree.rend();

		T	val = tree._root->getValue();
		// if (tree._last)
		// 	tree._last->getValue();
		bool	mine = 1;
		if (mine)
		{
			std::cout << "Tree start" << std::endl;
			tree.erase(val);
			std::cout << "Tree erase" << std::endl;
			// ++it;
			--it;
			std::cout << "Tree --" << std::endl;
			std::cout << "Tree::val : " << *it << std::endl;
		}

		std::cout << "Map start" << std::endl;
		

		m.erase(val);
		std::cout << "Map erase" << std::endl;
		// ++mit;
		--mit;
		std::cout << "Map --" << std::endl;
		std::cout << "Map::val : " << mit->first << std::endl;
	}
	else
	{
		if (tree.begin() != tree.end())
			std::cout << "Tree empty Iter : KO !!!!!!" << std::endl;
		std::cout << "Tree empty Iter : OK" << std::endl;
		if (m.begin() != m.end())
			std::cout << "Map empty Iter : KO !!!!!!" << std::endl;
		std::cout << "Map empty Iter : OK" << std::endl;
	}
	tree.clear();
	std::cout << "last : " << tree._last << std::endl;
	std::cout << "root : " << tree._root << std::endl;
	std::cout << "begin : " << tree._begin << std::endl;
	m.clear();
	checkContent(m, tree);
	displayHeader("testAvlRevIter End");
}

template<typename T>
void	testAvlIter(std::map<T, T>& m, ft::Avl<T, std::less<T>, std::allocator<T> >& tree)
{
	displayHeader("testAvlIter");
	{
		typename std::map<T, T>::iterator	mit = m.begin();
		typename ft::Avl<T, std::less<T>, std::allocator<T> >::iterator	it = tree.begin();

		for (it = tree.begin(); it != tree.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Tree traverse OK" << std::endl;
		for (mit = m.begin(); mit != m.end(); ++mit)
		{
			std::cout << mit->first << " ";
		}
		std::cout << std::endl;
		std::cout << "Map traverse OK" << std::endl;
	}
	if (!m.empty())
	{
		typename std::map<T, T>::iterator	mit = m.end();
		typename ft::Avl<T, std::less<T>, std::allocator<T> >::iterator	it = tree.end();

		T	val = T();
		if (tree._last)
			tree._last->getValue();
		(void)val;
		bool	mine = 1;
		if (mine)
		{
			std::cout << "Tree start" << std::endl;
			// tree.erase(val);
			std::cout << "Tree erase" << std::endl;
			// ++ite;
			--it;
			std::cout << "Tree --" << std::endl;
			std::cout << "Tree::val : " << *it << std::endl;
		}

		std::cout << "Map start" << std::endl;
		

		// m.erase(val);
		std::cout << "Map erase" << std::endl;
		// ++ite;
		--mit;
		std::cout << "Map --" << std::endl;
		std::cout << "Map::val : " << mit->first << std::endl;
	}
	else
	{
		if (tree.begin() != tree.end())
			std::cout << "Tree empty Iter : KO !!!!!!" << std::endl;
		std::cout << "Tree empty Iter : OK" << std::endl;
		if (m.begin() != m.end())
			std::cout << "Map empty Iter : KO !!!!!!" << std::endl;
		std::cout << "Map empty Iter : OK" << std::endl;
	}
	displayHeader("testAvlIter End");
}

void	testAvlIterator(int n)
{
	std::vector<int>	numbers;

	for (int i = 0; i < n; i++)
		numbers.push_back(std::rand() % n);

	
	std::map<int, int>	m;
	ft::Avl<int, std::less<int>, std::allocator<int> >	tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(numbers[i]);
		m.insert(std::make_pair(numbers[i], i));
	}
	std::cout << "show" << std::endl;
	tree.show();
	std::cout << "show End" << std::endl;
	testAvlRevIter(m, tree);
	testAvlIter(m, tree);


}