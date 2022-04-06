#include <iostream>

template <typename T>
T max(T x, T y);

int main()
{
	int i=10, j=20;
	double x=10.1, y=23.3;
	char a='x', b='z';

	std::cout << max<int>('c', 'j') << std::endl;
	std::cout << max(i, j) << std::endl;
	std::cout << max<>(i, j) << std::endl;
	std::cout << max(x, y) << std::endl;
	std::cout << max(a, b) << std::endl;

	return 0;
}