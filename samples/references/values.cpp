#include <algorithm>
#include <string>
#include <iostream>

class cl
{
	public:
	cl()
	{
		std::cout << "default const" << std::endl;
	}
	cl(int n)
	{
		std::cout << "param const" << std::endl;
	}
};

void	foo(const int& s)
{

}

void	bar(const int& s)
{
	std::cout << "const lvalue" << std::endl;
}

void	bar(int&& s)
{
	std::cout << "rvalue" << std::endl;
}

int main()
{
	int a = 11;
	const int ca = 55;
	bar(15);
	bar(a);
	bar(ca);
	bar(std::move(ca));
	return 0;
}