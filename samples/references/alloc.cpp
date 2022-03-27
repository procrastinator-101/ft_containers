#include <algorithm>
#include <string>
#include <iostream>

class cl
{
	public:
	// cl()
	// {
	// 	std::cout << "default const" << std::endl;
	// }
	cl(int n)
	{
		std::cout << "param const" << std::endl;
	}
};

int main()
{
	// int &ref = new int(5);

	// int (**p) () = new (int (*[7]) ());
	// delete [] p;
	int (**p) () = new (int (*) ());
	delete p;

	cl *ptr = new cl(5);
	return 0;
}