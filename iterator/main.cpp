#include <iomanip>
#include <ios>
#include <iostream>     // std::cout
#include <iterator>
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

template<typename T>
bool	operator==(ft::reverse_iterator<T>& a, std::reverse_iterator<T>& b)
{
	return a.base() == b.base();
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
		std::cout << "rit->_val == stdrit->_val" << " : " << (rit->_val == stdrit->_val) << std::endl;
	}
	
	std::cout << std::setw(20) << "ritEnd - rit == stdritEnd - stdrit" << " : " << (ritEnd - rit == stdritEnd - stdrit) << std::endl;
	std::cout << std::setw(20) << "rit - ritEnd == stdrit - stdritEnd" << " : " << (rit - ritEnd == stdrit - stdritEnd) << std::endl;

	int n = 10;

	ft::reverse_iterator<std::vector<cl>::iterator> iit = rit + n;
	std::reverse_iterator<std::vector<cl>::iterator> stdiit = stdrit + n;
	std::cout << std::setw(20) << "rit + n == stdrit + n" << " : " << (iit == stdiit) << std::endl;
	ft::reverse_iterator<std::vector<cl>::iterator> iit2 = ritEnd + n;
	std::reverse_iterator<std::vector<cl>::iterator> stdiit2 = stdritEnd + n;
	std::cout << std::setw(20) << "ritEnd + n == stdritEnd + n" << " : " << (iit2 == stdiit2) << std::endl;

	std::cout << std::setw(20) << "rit - ritEnd == stdrit - stdritEnd" << " : " << (rit - ritEnd == stdrit - stdritEnd) << std::endl;
	std::cout << std::setw(20) << "ritEnd - rit == stdritEnd - stdrit" << " : " << (ritEnd - rit == stdritEnd - stdrit) << std::endl;



	return 0;
}