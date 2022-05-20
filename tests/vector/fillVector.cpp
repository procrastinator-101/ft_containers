#include "testUtilities.hpp"
#include <sstream>

std::string	ft_itoa(int n)
{
	std::stringstream	ss;

	ss << n;
	return ss.str();
}

void	fillVector(std::vector<int>& vec, size_t n)
{
	for (size_t i = 0; i < n; i++)
		vec.push_back(std::rand() % n + 100);
}

void	fillVector(ft::vector<ft::court>& vec, size_t n)
{
	displaySubHeader("ft::fillVector");
	for (size_t i = 0; i < n; i++)
	{
		std::cout << "-----------------------------------------------------------------------" << std::endl;
		vec.push_back(std::string("|name ") + ft_itoa(std::rand() % 26) + "|");
		std::cout << "-----------------------------------------------------------------------" << std::endl;
	}
	displaySubHeader("ft::fillVector End");
}

void	fillVector(ft::vector<int>& vec, size_t n)
{
	for (size_t i = 0; i < n; i++)
		vec.push_back(std::rand() % n + 100);
}

void	fillVector(std::vector<ft::court>& vec, size_t n)
{
	displaySubHeader("std::fillVector");
	for (size_t i = 0; i < n; i++)
	{
		std::cout << "-----------------------------------------------------------------------" << std::endl;
		vec.push_back(std::string("|name ") + ft_itoa(std::rand() % 26) + "|");
		std::cout << "-----------------------------------------------------------------------" << std::endl;
	}
	displaySubHeader("std::fillVector End");
}