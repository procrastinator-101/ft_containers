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

int main()
{
	cl	obs[5];
}