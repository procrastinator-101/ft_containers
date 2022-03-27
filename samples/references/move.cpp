#include <algorithm>
#include <string>
#include <iostream>
#include <utility>

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

template<class T>
void	foo(T&& s)
{
	std::cout << "Universal foo " << s << std::endl; 	
}

template<class T>
void	foo(const T& s)
{
	std::cout << "const lvalue Foo " << s << std::endl; 	
}

void	foo(int& s)
{
	std::cout << "Foo " << s << std::endl; 	
}

int	bar(int&& s)
{
	std::cout << "/////////////////////////////" << std::endl;
	std::cout << s << std::endl;
	std::cout << "/////////////////////////////" << std::endl;
	int &&a = std::move(s);
	int j = 15;
	int &&p = std::move(5);
	return 0;
}

int main()
{
	cl	obs[5];

	int a = 11;
	const int b = 20;
	const int &ref = a;
	foo(15);
	foo(a);
	foo(b);
	foo(ref);
	foo(std::move(ref));
	return 0;
}