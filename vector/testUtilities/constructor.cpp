#include "court.hpp"
#include "display.hpp"
#include "testUtilities.hpp"
#include <memory>

void	testRangeConstructor(int n)
{
	displayHeader("testRangeConstructor");
	bool	ret;

	displaySubHeader("T = int");
	{
		std::vector<int>	sequence;
		fillVector(sequence, n);
		
		std::cout << "std" << std::endl;
		std::vector<int> a(sequence.begin(), sequence.end());
		std::cout << "ft" << std::endl;
		ft::vector<int> b(sequence.begin(), sequence.end());
		std::cout << "ftend" << std::endl;

		std::cout << a << std::endl;
		std::cout << b << std::endl;

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displaySubHeader("T = ft::court");
	{
		std::vector<ft::court>	sequence;
		fillVector(sequence, n);
		
		std::cout << "std" << std::endl;
		std::vector<ft::court> a(sequence.begin(), sequence.end());
		std::cout << "ft" << std::endl;
		ft::vector<ft::court> b(sequence.begin(), sequence.end());
		std::cout << "ftend" << std::endl;

		std::cout << a << std::endl;
		std::cout << b << std::endl;

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
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
		std::cout << "std" << std::endl;
		std::vector<ft::court>	a(n, val);
		std::cout << "ft" << std::endl;
		ft::vector<ft::court>		b(n, val);

		check(a, b);
	}
	{
		ft::court	val(std::string("|name ") + ft_itoa(std::rand() % 26) + "|");
		std::cout << "std" << std::endl;
		std::vector<ft::court>	a(n, val);
		std::cout << "ft" << std::endl;
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

void	testSfinae()
{
	displayHeader("testSfinae");
	displaySubHeader("T = int");
	const int a = 2, b = 6;
	ft::vector<int>v(a, b);
	displayHeader("testSfinae End");
	std::allocator<char> all;
	char *ptr;
	char arr[3];
	std::vector<int>ham(15.4f, 'g');
	// ft::vector<char>v2(1e7, 'c', all);
	// std::vector<char>v3(1e7, 'c', all);
	// v2.assign(1e7, 'h');
	// v3.assign(1e7, 'h');

}

void	testConstructor()
{
	int n = std::rand() % 100;;
	testDefaultConstructor();
	testParamConstructor(n);
	testRangeConstructor(n);
}