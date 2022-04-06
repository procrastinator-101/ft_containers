#include <iostream>

template <typename T>
T max(T x, T y)
{
	std::cout << "max" << std::endl;
    return (x > y) ? x : y;
}

template int max(int x, int y);
template double max(double x, double y);
template char max(char x, char y);