#include <string>
#include <iostream>

class cl
{
	public:

	int a;

	cl()
	{
		std::cout << "default const" << std::endl;
	}
	cl(int n)
	{
		std::cout << "param const" << std::endl;
	}
	void	cry()
	{
		std::cout << "CRY CRY CRY" << std::endl;
	}
};

int main()
{
	int	cl::*ap;

	cl	obs[5];
	cl k;

	ap = &cl::a;
}