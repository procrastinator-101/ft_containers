#include "court.hpp"
#include "testUtilities.hpp"

static int n = 10;//a, b initial size
static int size = 20;

void	testAssignmentOperator()
{
	displayHeader("testAssignmentOperator");
	bool	ret;

	displaySubHeader("T = int");
	{
		std::vector<int>	a;
		fillVector(a, n);
		ft::vector<int> b(a.begin(), a.end());

		std::vector<int> asrc;
		fillVector(asrc, size);
		ft::vector<int> bsrc(asrc.begin(), asrc.end());

		std::cout << "std" << std::endl;
		a = asrc;
		std::cout << "ft" << std::endl;
		b = bsrc;
		std::cout << "ftend" << std::endl;

		std::cout << a << std::endl;
		std::cout << b << std::endl;

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displaySubHeader("T = ft::court");
	{
		std::vector<ft::court>	a;
		fillVector(a, n);
		ft::vector<ft::court> b(a.begin(), a.end());

		std::vector<ft::court> asrc;
		fillVector(asrc, size);
		ft::vector<ft::court> bsrc(asrc.begin(), asrc.end());

		std::cout << "std" << std::endl;
		a = asrc;
		std::cout << "ft" << std::endl;
		b = bsrc;
		std::cout << "ftend" << std::endl;

		std::cout << a << std::endl;
		std::cout << b << std::endl;

		check(a, b);
		ret = ft::equal(a.rbegin(), a.rend(), b.rbegin());
		std::cout << std::setw(30) << "reverse iterator " << ": " << ret << std::endl;
	}
	displayHeader("testAssignmentOperator End");
}