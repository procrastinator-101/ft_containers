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


void	bar(int& s)
{
	std::cout << "non-const int" << std::endl;
}

template<class T>
void	bar(T&& s)
{
	std::cout << "uni value" << std::endl;
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