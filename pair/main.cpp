#include "make_pair.hpp"
#include "pair.hpp"
#include <string>
#include <iostream>

int main()
{
	ft::pair<int, std::string> p1(1,"abc");
	ft::pair<int, std::string> p2 = ft::make_pair(p1.first, "258");

	std::cout << p1.first << " " << p1.second << std::endl;
	std::cout << p2.first << " " << p2.second << std::endl;
}