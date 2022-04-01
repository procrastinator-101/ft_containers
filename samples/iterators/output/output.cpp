#include <iostream>
#include <vector>
#include "input_iterator.hpp"


class cl
{
	int _n;

	public:
	cl(int n = 0) : _n(n){}
	cl(const cl& src) : _n(src._n){}

	cl	&operator=(const cl& rop)
	{
		if (this == &rop)
			return *this;
		_n = rop._n;
		return *this;
	}
	void	setN(int n)
	{
		_n = n;
	}
	int	getN() const
	{
		return _n;
	}
};



void	clTest()
{
	int n = 10;
	cl arr[n];

	for (int i = 0; i < n; i++)
		arr[i].setN(i);
	ft::input_iterator<cl>	it(arr);
	ft::input_iterator<cl>	clone = it;
	ft::input_iterator<cl>	end(arr + n);

	std::cout << "============================== it ===========================" << std::endl;
	for (;it != end; ++it)
		std::cout << it->getN() << std::endl;
	std::cout << "============================== * ===========================" << std::endl;
	*clone = arr[2];
	std::cout << (*clone).getN() << std::endl;
	clone->setN(20);
	std::cout << (*clone).getN() << std::endl;
	std::cout << "============================== clone ===========================" << std::endl;
	for (;clone != end;)
		std::cout << (*clone++).getN() << std::endl;
	
	std::cout << "============================== tmp ===========================" << std::endl;
	ft::input_iterator<cl> tmp;
	tmp = it;
	if (tmp == it)
		std::cout << "|" << tmp->getN() << "|" << std::endl;
	std::cout << "=============================================================" << std::endl;
}

void	intTest()
{
	int n = 10;
	int arr[n];

	for (int i = 0; i < n; i++)
		arr[i] = i;
	ft::input_iterator<int>	it(arr);
	ft::input_iterator<int> clone = it;
	ft::input_iterator<int>	end(arr + n);

	std::cout << "============================== it ===========================" << std::endl;
	for (;it != end; ++it)
		std::cout << *it << std::endl;
	std::cout << "============================== clone ===========================" << std::endl;
	for (;clone != end; clone++)
		std::cout << *clone << std::endl;
	
	std::cout << "============================== tmp ===========================" << std::endl;
	ft::input_iterator<int> tmp;
	tmp = it;
	if (tmp == it)
		std::cout << "|" << *tmp << "|" << std::endl;
	std::cout << "=============================================================" << std::endl;
}

int	main()
{
	intTest();
	clTest();
	return 0;
}