#include <iomanip>
#include <ios>
#include <iostream>     // std::cout
#include <ostream>
#include <sys/_types/_size_t.h>
#include <typeinfo>     // typeid
#include <vector>     // typeid

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

struct cl
{
	int _val;

	cl(int val) : _val(val){};

	void	show()
	{
		std::cout << "hi " << _val << std::endl;
	}
};

bool	operator==(const cl& lhs, const cl& rhs)
{
	return lhs._val == rhs._val;
}

std::ostream	&operator<<(std::ostream& ostr, const cl& obj)
{
	ostr << obj._val;
	return ostr;
}

int main()
{
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator" << std::endl;
	
	std::vector<cl> nums;
	for (int i = 0; i < 10; i++)
		nums.push_back(i);
	ft::reverse_iterator<std::vector<cl>::iterator> rit(nums.end());
	ft::reverse_iterator<std::vector<cl>::iterator> ritEnd(nums.begin());

	std::reverse_iterator<std::vector<cl>::iterator> stdrit(nums.end());
	std::reverse_iterator<std::vector<cl>::iterator> stdritEnd(nums.begin());
	

	std::cout << std::boolalpha << std::left;
	std::cout << std::setw(20) << "rit == stdrit" << " : " << (rit.base() == stdrit.base()) << std::endl;
	std::cout << std::setw(20) << "ritEnd == stdritEnd" << " : " << (ritEnd.base() == stdritEnd.base()) << std::endl;
	while (stdritEnd != stdrit)
	{
		std::cout << *stdrit << " ";
		++stdrit;
	}
	std::cout << std::endl;
	while (ritEnd != rit)
	{
		std::cout << *rit << " ";
		++rit;
	}
	std::cout << std::endl;

	rit -= nums.size();
	stdrit -= nums.size();
	rit->show();
	stdrit->show();
	for (size_t i = 0; i < nums.size(); i++)
	{
		std::cout << "rit[" << i << "] == stdrit[" << i << "] : " << (rit[i] == stdrit[i]) << std::endl;
	}
	
	return 0;
}