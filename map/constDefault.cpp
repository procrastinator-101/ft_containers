#include <iostream>

class cl
{
	public:
		cl()
		{
			std::cout << "cl::Default constructor" << std::endl;
		}

		~cl()
		{
			std::cout << "cl::Destructor" << std::endl;
		}

		cl(const cl& src)
		{
			std::cout << "cl::Copy constructor" << std::endl;
		}
};

class other
{
	cl	_data;

	public:
		other() : _data()
		{
			std::cout << "other::Default constructor" << std::endl;
		}

		other(const other& src) : _data(src._data)
		{
			std::cout << "other::Copy constructor" << std::endl;
		}

		~other()
		{
			std::cout << "other::Destructor" << std::endl;
		}
};

int	main()
{
	other	b;
	return 0;
}