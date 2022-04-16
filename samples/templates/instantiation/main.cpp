#include "cl.hpp"

extern template struct cl<int>;	//explicit instantiaton declaration

// cl<int>::high = 0;

void	func();

int main()
{
	cl<int> ob;

	ob.foo();
	func();
	return 0;
}