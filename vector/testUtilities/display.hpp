#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <ostream>
#include <vector>
#include <iostream>

namespace ft
{
	template < class T, class Alloc>
	class vector;
}

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

template<typename INPUT_ITERATOR>
void	showPair(INPUT_ITERATOR first, INPUT_ITERATOR last)
{
	std::cout << "======================= Show =========================" << std::endl;
	while (first != last)
	{
		std::cout << first->first << " ";
		++first;
	}
	std::cout << std::endl;
	std::cout << "======================================================" << std::endl;
}

template<typename T, typename Alloc>
std::ostream	&operator<<(std::ostream& ostr, const ft::vector<T, Alloc>& v)
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
	ostr << "======================== STD =========================" << std::endl;
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

void		displayHeader(const std::string& str);
void		displaySubHeader(const std::string& str);
std::string	centerString(int width, const std::string& str);

#endif