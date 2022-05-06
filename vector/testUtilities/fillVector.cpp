#include "court.hpp"
#include "testUtilities.hpp"

void	fillVector(std::vector<int>& vec, size_t n)
{
	for (size_t i = 0; i < n; i++)
		vec.push_back(std::rand() % n + 100);
}

void	fillVector(ft::vector<ft::court>& vec, size_t n)
{
	// std::cout << "in" << std::endl;
	for (size_t i = 0; i < n; i++)
	{
		// std::cout << "-----------------------------------------------------------------------" << std::endl;
		vec.push_back(std::string("|name ") + std::to_string(std::rand() % 26) + "|");
		// std::cout << "-----------------------------------------------------------------------" << std::endl;
	}
	// std::cout << "out" << std::endl;
}

void	fillVector(ft::vector<int>& vec, size_t n)
{
	for (size_t i = 0; i < n; i++)
		vec.push_back(std::rand() % n + 100);
}

void	fillVector(std::vector<ft::court>& vec, size_t n)
{
	// std::cout << "-in" << std::endl;
	for (size_t i = 0; i < n; i++)
	{
		// std::cout << "-----------------------------------------------------------------------" << std::endl;
		vec.push_back(std::string("|name ") + std::to_string(std::rand() % 26) + "|");
		// std::cout << "-----------------------------------------------------------------------" << std::endl;
	}
	// std::cout << "-out" << std::endl;
}