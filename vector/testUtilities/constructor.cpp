#include "testUtilities.hpp"

void	testConstructor()
{
	std::cout << "///////////////////// Constructor ///////////////////////" << std::endl;
	std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	try
	{
		std::vector<ft::court>stdVector(6);
		std::cout << "========================================================" << std::endl;
		std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
		std::cout << "========================================================" << std::endl;
		std::vector<ft::court>clone(stdVector);
		std::cout << "========================================================" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	try
	{
		ft::vector<ft::court>stdVector(6);
		std::cout << "========================================================" << std::endl;
		std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
		std::cout << "========================================================" << std::endl;
		ft::vector<ft::court>clone(stdVector);
		std::cout << "========================================================" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
	std::cout << "/////////////////// Constructor End /////////////////////" << std::endl;
}