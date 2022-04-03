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

template<class InputIterator>
void	iterate(InputIterator first, InputIterator last)
{
	while (first != last)
	{
		std::cout << first->getN() << std::endl;
		++first;
	}
}

void	clTest()
{
	int n = 10;
	cl arr[n];

	for (int i = 0; i < n; i++)
		arr[i].setN(i);
	ft::input_iterator<cl>	it(arr);
	ft::input_iterator<cl>	end(arr + n);
	iterate(it, end);
}

int	main()
{
	clTest();
	return 0;
}