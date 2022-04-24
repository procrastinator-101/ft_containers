#ifndef CHECKER_HPP
# define CHECKER_HPP

#include <vector>
#include <ostream>
#include <iomanip>
#include <iostream>

#include "court.hpp"
#include "display.hpp"
#include "../vector.hpp"

#include "../../algorithm/equal.hpp"
#include "../../algorithm/lexicographical_compare.hpp"

template<typename T>
void	check(std::vector<T>& a, ft::vector<T>& b)
{
	bool	ret;

	std::cout << std::setw(30) << "size " << ": " << (a.size() == b .size()) << std::endl;
	std::cout << std::setw(30) << "capacity " << ": " << (a.capacity() == b.capacity()) << std::endl;

	ret = ft::equal(a.begin(), a.end(), b.begin());
	std::cout << std::setw(30) << "val 1 " << ": " << ret << std::endl;
	ret = ft::equal(b.begin(), b.end(), a.begin());
	std::cout << std::setw(30) << "val 2 " << ": " << ret << std::endl;
}

#endif