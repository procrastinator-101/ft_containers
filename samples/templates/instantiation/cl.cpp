#include "cl.hpp"


template<>
struct cl<int>
{
	static int high;
	void	foo()
	{
		cout << "integer spec" << endl;
	}

	void	wheel(); 
};

int cl<int>::high = 165;

// template<> struct cl<int>;	//explicit instantiaton definition
template<> struct cl<int>;	//explicit instantiaton definition


void	func()
{
	cl<int> ob;

	ob.foo();
}