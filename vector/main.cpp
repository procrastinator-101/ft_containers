#include <exception>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

#include "vector.hpp"

#include "court.hpp"

void	testVector();

int main()
{
	std::cout << court::getCount() << std::endl;
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	try
	{
		std::vector<court>stdVector(6);
		std::cout << "========================================================" << std::endl;
		std::cout << court::getCount() << std::endl;
		std::cout << "========================================================" << std::endl;
		std::vector<court>clone(stdVector);
		std::cout << "========================================================" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	std::cout << court::getCount() << std::endl;
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	try
	{
		ft::vector<court>stdVector(6);
		std::cout << "========================================================" << std::endl;
		std::cout << court::getCount() << std::endl;
		std::cout << "========================================================" << std::endl;
		ft::vector<court>clone(stdVector);
		std::cout << "========================================================" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	std::cout << court::getCount() << std::endl;
	return 0;
}