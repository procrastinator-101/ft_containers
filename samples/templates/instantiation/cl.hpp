#ifndef CL_HPP
# define CL_HPP

#include <iostream>

using namespace std;

template<typename T>
struct	cl
{
	static int high;
	void	foo()
	{
		cout << "foo primary" << endl;
	}

	void	bar();
};


// extern template struct cl<int>;	//explicit instantiaton declaration
// template<> struct cl<int>;	//explicit instantiaton definition

#endif