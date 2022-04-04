#include <algorithm>
#include <string>
#include <iostream>
#include <utility>


void	bar(int& s)
{
	std::cout << "lvalue" << std::endl;
}

void	bar(int&& s)
{
	std::cout << "rvalue" << std::endl;
}

template<class T>
void	foo(T&& s)
{
	bar(std::forward<T>(s));
}

int main()
{
	int nb = 10;
	const int cnb = nb;

	int &rl = nb;
	int &&rr = 20;

	foo(rl);
	foo(rr);

	foo(nb);
	foo(15);
	// foo(cnb);
	// foo(std::move(cnb));


	return 0;
}