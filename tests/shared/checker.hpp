#ifndef CHECKER_HPP
# define CHECKER_HPP

#include "../../map/map.hpp"
// #include "../../stack/stack.hpp"
#include "../../vector/vector.hpp"

#include <map>
#include <stack>
#include <vector>

#include <iomanip>
#include <iostream>

template<typename T>
void	checkVector(std::vector<T>& a, ft::vector<T>& b)
{
	bool	ret;

	std::cout << std::boolalpha << std::right;
	std::cout << std::setw(30) << "size " << ": " << (a.size() == b .size()) << std::endl;
	std::cout << std::setw(30) << "capacity " << ": " << (a.capacity() == b.capacity()) << std::endl;

	ret = ft::equal(a.begin(), a.end(), b.begin());
	std::cout << std::setw(30) << "val 1 " << ": " << ret << std::endl;
	ret = ft::equal(b.begin(), b.end(), a.begin());
	std::cout << std::setw(30) << "val 2 " << ": " << ret << std::endl;
}

template <class Key, class T>
void	checkMap(std::map<Key, T>& a, ft::map<Key, T>& b)
{
	bool	ret;

	std::cout << std::boolalpha << std::right;
	std::cout << std::setw(30) << "size " << ": " << (a.size() == b.size()) << std::endl;

	ret = ft::equal(a.begin(), a.end(), b.begin());
	std::cout << std::setw(30) << "val 1 " << ": " << ret << std::endl;
	ret = ft::equal(b.begin(), b.end(), a.begin());
	std::cout << std::setw(30) << "val 2 " << ": " << ret << std::endl;
}

template<typename T>
void	checkEqaulity(T& a, T& b, const std::string& msg)
{
	bool ret;

	ret = a == b;
	std::cout << std::boolalpha << std::right;
	std::cout << std::setw(30) << msg << " : " << ret << std::endl;
}

#endif