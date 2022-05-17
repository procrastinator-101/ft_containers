#include "../avl.hpp"
#include "../../vector/testUtilities/display.hpp"

#include <map>
#include <memory>
#include <utility>
#include <random>
#include <chrono>
#include <algorithm>


static bool isStdFirst = 0;

template<typename T>
void	checkContent(std::map<T, T>& m, ft::Avl<T, std::less<T>, std::allocator<T> >& tree)
{
	displaySubHeader("checkContent");
	typename std::map<T, T>::reverse_iterator	mit = m.rbegin();
	typename ft::Avl<T, std::less<T>, std::allocator<T> >::reverse_iterator	it = tree.rbegin();
	while (it != tree.rend())
	{
		if (mit->first != *it)
			std::cout << "RevIter KO !!!!" << std::endl;
		std::cout << *it << " ";
		++it;
		++mit;
	}
	std::cout << std::endl;
	displaySubHeader("checkContent End");
}

template<typename T>
void	testOutOfRangeIter(std::map<T, T>& subject, const T& toErase)
{
	displaySubHeader("Map testOutOfRangeIter");
	typename std::map<T, T>::iterator	it = subject.end();
	showPair(subject.begin(), subject.end());
	subject.erase(toErase);
	std::cout << "Erase : OK" << std::endl;
	--it;
	std::cout << "Decrement : OK" << std::endl;
	std::cout << "lastVal : " << it->first << std::endl;
	displaySubHeader("Map testOutOfRangeIter End");
}

template<typename T>
void	testOutOfRangeIter(ft::Avl<T, std::less<T>, std::allocator<T> >& subject, const T& toErase)
{
	displaySubHeader("Tree testOutOfRangeIter");
	typename ft::Avl<T, std::less<T>, std::allocator<T> >::iterator	it = subject.end();
	show(subject.begin(), subject.end());
	subject.erase(toErase);
	std::cout << "Erase : OK" << std::endl;
	--it;
	std::cout << "Decrement : OK" << std::endl;
	std::cout << "lastVal : " << *it << std::endl;
	displaySubHeader("Tree testOutOfRangeIter End");
}

template<typename T>
void	testEmptyMap(std::map<T, T>& subject)
{
	displaySubHeader("Map testEmpties");
	if (subject.begin() != subject.end())
		std::cout << "Map empty Iter : KO !!!!!!" << std::endl;
	std::cout << "Map empty Iter : OK" << std::endl;
	if (subject.rbegin() != subject.rend())
		std::cout << "Map empty Reverse Iter : KO !!!!!!" << std::endl;
	std::cout << "Map empty Reverse Iter : OK" << std::endl;
	displaySubHeader("Map testEmpties End");
}

template<typename T>
void	testEmptyTree(ft::Avl<T, std::less<T>, std::allocator<T> >& subject)
{
	displaySubHeader("Tree testEmpties");
	if (subject.begin() != subject.end())
		std::cout << "Tree empty Iter : KO !!!!!!" << std::endl;
	std::cout << "Tree empty Iter : OK" << std::endl;
	if (subject.rbegin() != subject.rend())
		std::cout << "Tree empty Reverse Iter : KO !!!!!!" << std::endl;
	std::cout << "Tree empty Reverse Iter : OK" << std::endl;
	displaySubHeader("Tree testEmpties End");
}

template<typename T>
void	testEmpties(std::map<T, T>& m, ft::Avl<T, std::less<T>, std::allocator<T> >& tree)
{
	if (isStdFirst)
	{
		testEmptyMap(m);
		testEmptyTree(tree);
	}
	else
	{
		testEmptyTree(tree);
		testEmptyMap(m);
	}
}

template<typename T>
void	testAvlRevIter(std::map<T, T>& m, ft::Avl<T, std::less<T>, std::allocator<T> >& tree)
{
	displayHeader("testAvlRevIter");
	checkContent(m, tree);
	if (!m.empty())
	{
		T	val = m.begin()->first;
		if (isStdFirst)
		{
			testOutOfRangeIter(m, val);
			testOutOfRangeIter(tree, val);
		}
		else
		{
			testOutOfRangeIter(tree, val);
			testOutOfRangeIter(m, val);
		}
	}
	else
	{
		testEmpties(m, tree);
	}
	m.clear();
	tree.clear();
	checkContent(m, tree);
	displayHeader("testAvlRevIter End");
}

template<typename T>
void	testAvlIter(std::map<T, T>& m, ft::Avl<T, std::less<T>, std::allocator<T> >& tree)
{
	displayHeader("testAvlIter");
	{
		showPair(m.begin(), m.end());
		show(tree.begin(), tree.end());
	}
	if (!m.empty())
	{
		T	val = m.begin()->first;
		if (isStdFirst)
		{
			testOutOfRangeIter(m, val);
			testOutOfRangeIter(tree, val);
		}
		else
		{
			testOutOfRangeIter(tree, val);
			testOutOfRangeIter(m, val);
		}
	}
	else
	{
		testEmpties(m, tree);
	}
	displayHeader("testAvlIter End");
}

void	testConstAvlIter(std::map<int, int>& m, ft::Avl<int, std::less<int>, std::allocator<int> >& tree)
{
	displayHeader("testConstAvlIter");
	ft::Avl<int, std::less<int>, std::allocator<int> >::const_iterator	it = tree.begin();
	displayHeader("testConstAvlIter End");
}

void	testAvlIterator(int n)
{
	std::vector<int>	numbers;

	for (int i = 0; i < n; i++)
		numbers.push_back(i);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine(seed);
    std::shuffle(numbers.begin(), numbers.end(), engine);
	
	std::map<int, int>	m;
	ft::Avl<int, std::less<int>, std::allocator<int> >	tree;

	for (int i = 0; i < n; i++)
	{
		tree.insert(numbers[i]);
		m.insert(std::make_pair(numbers[i], i));
	}
	testAvlRevIter(m, tree);
	testAvlIter(m, tree);
}