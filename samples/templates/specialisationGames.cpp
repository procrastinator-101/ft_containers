#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x > y) ? x : y;
}

template <>
int max<int>(int x, int y)
{
	std::cout << "Inside max<int> specialization.\n";
    return (x > y) ? x : y;
}


int max(int x, int y)
{
	std::cout << "Inside max int specialization.\n";
	return (x > y) ? x : y;
}

int main()
{
	int i=10, j=20;
	double x=10.1, y=23.3;
	char a='x', b='z';

	std::cout << "Original i, j: " << i << ' ' << j << '\n';
	std::cout << "Original x, y: " << x << ' ' << y << '\n';
	std::cout << "Original a, b: " << a << ' ' << b << '\n';

	max(i, j);
	max<int>('c', 'j');
	max<>(i, j);
	max(x, y);
	max(a, b);

	std::cout << "Swapped i, j: " << i << ' ' << j << '\n';
	std::cout << "Swapped x, y: " << x << ' ' << y << '\n';
	std::cout << "Swapped a, b: " << a << ' ' << b << '\n';
	return 0;
}