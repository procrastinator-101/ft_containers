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

int	bar()
{
	int s = 5;
	return s;
}

int main()
{
	cl	obs[5];

	int a = 11;
	foo(15);
	foo(a);
	std::cout << -a << std::endl;

	std::cout << bar() << std::endl;
}