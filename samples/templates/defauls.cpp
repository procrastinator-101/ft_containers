#include <iostream>

float s = 15.36;

template <typename T = int>
T max(T x, T y)
{
	std::cout << typeid(T).name() << std::endl;
    return (x > y) ? x : y;
}

int main()
{
	
	std::cout << max(4.6, 53.2) << std::endl;
	return 0;
}