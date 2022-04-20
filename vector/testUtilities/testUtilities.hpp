#ifndef TESTUTILITIES_HPP
# define TESTUTILITIES_HPP

#include <ostream>
#include <vector>
#include <iostream>

#include "court.hpp"
#include "../vector.hpp"

void	testInsert();
void	testConstructor();

void	fillVector(ft::vector<int>& vec, size_t n);
void	fillVector(ft::vector<ft::court>& vec, size_t n);

void	fillVector(std::vector<int>& vec, size_t n);
void	fillVector(std::vector<ft::court>& vec, size_t n);


template<typename INPUT_ITERATOR>
void	show(INPUT_ITERATOR first, INPUT_ITERATOR last)
{
	std::cout << "======================= Show =========================" << std::endl;
	while (first != last)
	{
		std::cout << *first << " ";
		++first;
	}
	std::cout << std::endl;
	std::cout << "======================================================" << std::endl;
}

template<typename T>
std::ostream	&operator<<(std::ostream& ostr, const ft::vector<T>& v)
{
	ostr << "======================== FT ==========================" << std::endl;
	for (size_t i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	ostr << std::endl;
	ostr << "===================== capacity =======================" << std::endl;
	ostr << "max  = " << v.max_size() << std::endl;
	ostr << "size = " << v.size() << std::endl;
	ostr << "cap  = " << v.capacity() << std::endl;
	ostr << "======================================================" << std::endl;
	return ostr;
}

template<typename T>
std::ostream	&operator<<(std::ostream& ostr, const std::vector<T>& v)
{
	ostr << "======================== FT ==========================" << std::endl;
	for (size_t i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	ostr << std::endl;
	ostr << "===================== capacity =======================" << std::endl;
	ostr << "max  = " << v.max_size() << std::endl;
	ostr << "size = " << v.size() << std::endl;
	ostr << "cap  = " << v.capacity() << std::endl;
	ostr << "======================================================" << std::endl;
	return ostr;
}

#endif