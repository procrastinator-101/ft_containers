#include <iostream>
#include <vector>
#include "output_iterator.hpp"


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
	cl	tmp;

	ft::output_iterator<cl>	it(arr);
	ft::output_iterator<cl>	clone = it;
	ft::output_iterator<cl>	end(arr + n);

	std::cout << "============================== it ===========================" << std::endl;
	for (int i = 0; i < n; i++)
	{
		tmp.setN(i);
		*it = tmp;
		++it;
	}
	for (int i = 0; i < n; i++)
		std::cout << arr[i].getN() << " ";
	std::cout << std::endl;
	std::cout << "============================== * ============================" << std::endl;
	*clone = arr[2];
	std::cout << arr[0].getN() << std::endl;
	std::cout << "============================== clone ========================" << std::endl;
	for (int i = 0; i < n; i++)
	{
		tmp.setN(i);
		*clone = tmp;
		++clone;
	}
	for (int i = 0; i < n; i++)
		std::cout << arr[i].getN() << " ";
	std::cout << std::endl;
	std::cout << "============================== tmp ==========================" << std::endl;
	ft::output_iterator<cl> h;
	h = it;
	std::cout << "=============================================================" << std::endl;
}

void	intTest()
{
	int n = 10;
	int arr[n];

	ft::output_iterator<int>	it(arr);
	ft::output_iterator<int>	clone = it;
	ft::output_iterator<int>	end(arr + n);

	std::cout << "============================== it ===========================" << std::endl;
	for (int i = 0; i < n; i++)
	{
		*it = i;
		++it;
	}
	for (int i = 0; i < n; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	std::cout << "============================== * ============================" << std::endl;
	*clone = arr[2];
	std::cout << arr[0] << std::endl;
	std::cout << "============================== clone ========================" << std::endl;
	for (int i = 0; i < n; i++)
	{
		*clone = i;
		++clone;
	}
	for (int i = 0; i < n; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	std::cout << "============================== tmp ==========================" << std::endl;
	ft::output_iterator<int> h;
	h = it;
	std::cout << "=============================================================" << std::endl;
}

int	main()
{
	intTest();
	clTest();
	return 0;
}