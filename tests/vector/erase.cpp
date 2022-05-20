#include "checker.hpp"
#include "court.hpp"
#include "display.hpp"
#include "testUtilities.hpp"

template<typename T>
void	testErasePosition(int n, int position)
{
	displayHeader("testErasePosition");
	std::vector<T>	a;
	fillVector(a, n);

	ft::vector<T>	b(a.begin(), a.end());
	check(a, b);

	std::cout << "n : " << n << " position : " << position << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	a.erase(a.begin() + position);
	b.erase(b.begin() + position);
	check(a, b);
	displayHeader("testErasePosition End");
}

template<typename T>
void	testEraseRange(int n, int range[2])
{
	displayHeader("testEraseRange");
	std::vector<T>	a;
	fillVector(a, n);

	ft::vector<T>	b(a.begin(), a.end());
	check(a, b);

	std::cout << "n : " << n << " start : " << range[0] << " end : " << range[1] << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	a.erase(a.begin() + range[0], a.begin() + range[1]);
	b.erase(b.begin() + range[0], b.begin() + range[1]);
	check(a, b);
	displayHeader("testEraseRange End");
}

void	testErase(int n)
{
	std::cout << "n : " << n << std::endl;
	int range[2];
	int	position;

	if (!n)
		n = 10 + std::rand() % MAX_N;
	range[0] = std::rand() % n;
	range[1] = range[0] + (std::rand() % (n - range[0]));
	position = std::rand() % n;
	

	std::cout << "n : " << n << " start : " << range[0] << " end : " << range[1] << std::endl;
	testErasePosition<int>(n, position);
	testErasePosition<ft::court>(n, position);
	testEraseRange<int>(n, range);
	testEraseRange<ft::court>(n, range);
}