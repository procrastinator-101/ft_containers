#include "testUtilities.hpp"

void	testRangeConstructor(int n)
{
	displayHeader("testRangeConstructor");
	bool	ret;

	displaySubHeader("T = int");
	std::cout << std::boolalpha << std::left;
	{
		std::vector<int>	a;
		fillVector(a, n);
		ft::vector<int> b(a.begin(), a.end());

		check(a, b);
	}
	{
		std::vector<ft::court>	a;
		fillVector(a, n);
		ft::vector<ft::court> b(a.rbegin(), a.rend());

		std::cout << a << std::endl;
		std::cout << b << std::endl;

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.begin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displaySubHeader("T = ft::court");
	{
		std::vector<ft::court>	a;
		fillVector(a, n);
		ft::vector<ft::court> b(a.begin(), a.end());

		check(a, b);
	}
	{
		std::vector<ft::court>	a;
		fillVector(a, n);
		ft::vector<ft::court> b(a.rbegin(), a.rend());

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.begin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displayHeader("testRangeConstructor End");

}

void	testParamConstructor(int n)
{
	displayHeader("testParamConstructor");
	bool	ret;

	displaySubHeader("T = int");
	std::cout << std::boolalpha << std::left;
	{
		int	val = rand() % 1000;
		std::vector<int>	a(n, val);
		ft::vector<int>		b(n, val);

		check(a, b);
	}
	{
		int	val = rand() % 1000;
		std::vector<int>	a(n, val);
		ft::vector<int>		b(n, val);

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displaySubHeader("T = ft::court");
	{
		ft::court	val(std::string("|name ") + ft_itoa(std::rand() % 26) + "|");
		std::vector<ft::court>	a(n, val);
		ft::vector<ft::court>		b(n, val);

		check(a, b);
	}
	{
		ft::court	val(std::string("|name ") + ft_itoa(std::rand() % 26) + "|");
		std::vector<ft::court>	a(n, val);
		ft::vector<ft::court>		b(n, val);

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displayHeader("testParamConstructor End");
}

void	testDefaultConstructor()
{
	displayHeader("testDefaultConstructor");
	bool	ret;

	displaySubHeader("T = int");
	std::cout << std::boolalpha << std::left;
	{
		std::vector<int>	a;
		ft::vector<int>		b;

		check(a, b);
	}
	{
		std::vector<int>	a;
		ft::vector<int>		b;

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displaySubHeader("T = ft::court");
	{
		std::vector<ft::court>	a;
		ft::vector<ft::court>	b;

		check(a, b);
	}
	{
		std::vector<ft::court>	a;
		ft::vector<ft::court>	b;

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displayHeader("testDefaultConstructor End");
}

void	verboseTestParamConstructor()
{
	std::cout << "///////////////////// Constructor ///////////////////////" << std::endl;
	std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	try
	{
		std::vector<ft::court>stdVector(6);
		std::cout << "========================================================" << std::endl;
		std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
		std::cout << "========================================================" << std::endl;
		std::vector<ft::court>clone(stdVector);
		std::cout << "========================================================" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	try
	{
		ft::vector<ft::court>stdVector(6);
		std::cout << "========================================================" << std::endl;
		std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
		std::cout << "========================================================" << std::endl;
		ft::vector<ft::court>clone(stdVector);
		std::cout << "========================================================" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;
	std::cout << "ft::court::count  = " << ft::court::getCount() << std::endl;
	std::cout << "/////////////////// Constructor End /////////////////////" << std::endl;
}

void	testConstructor()
{
	int n = 10;
	testDefaultConstructor();
	testRangeConstructor(n);
	testParamConstructor(n);
}