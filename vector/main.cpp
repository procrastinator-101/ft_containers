#include <exception>
#include <memory>
#include <vector>
#include <iostream>

#include "vector.hpp"

int main()
{
	int n = 19;

	std::cout << "======================================================" << std::endl;
	std::vector<int>	nums;

	std::cout << "max  = " << nums.max_size() << std::endl;
	std::cout << "size = " << nums.size() << std::endl;
	std::cout << "cap  = " << nums.capacity() << std::endl;

	for (int i = 0; i < n; i++)
		nums.push_back(i);
	for (int i = 0; i < n; i++)
		std::cout << nums[i] << " ";
	std::cout << std::endl;

	nums.resize(55);
	nums.clear();
	std::cout << "max  = " << nums.max_size() << std::endl;
	std::cout << "size = " << nums.size() << std::endl;
	std::cout << "cap  = " << nums.capacity() << std::endl;
	std::cout << "======================================================" << std::endl;
	
	try
	{
		std::cout << nums.at(20);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "======================================================" << std::endl;
	std::allocator<int> s;

	std::cout << nums.max_size() << std::endl;
	std::cout << "======================================================" << std::endl;

	std::cout << "======================================================" << std::endl;
	ft::vector<int>	nbs;

	std::cout << "max  = " << nbs.max_size() << std::endl;
	std::cout << "size = " << nbs.size() << std::endl;
	std::cout << "cap  = " << nums.capacity() << std::endl;

	for (int i = 0; i < n; i++)
		nbs.push_back(i);
	for (int i = 0; i < n; i++)
		std::cout << nbs[i] << " ";
	std::cout << std::endl;

	nbs.resize(55);
	nbs.clear();
	std::cout << "max  = " << nbs.max_size() << std::endl;
	std::cout << "size = " << nbs.size() << std::endl;
	std::cout << "cap  = " << nbs.capacity() << std::endl;
	std::cout << "======================================================" << std::endl;
	try
	{
		std::cout << nbs.at(20);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}