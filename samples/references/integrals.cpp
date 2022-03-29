#include <algorithm>
#include <string>
#include <iostream>

void foo(int f)
{
	std::cout << f << std::endl;
}

int main()
{
	int a = 11;
	const int ca = 55;
	foo(static_cast<unsigned>(-15));
	return 0;
}