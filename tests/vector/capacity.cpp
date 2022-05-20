#include "court.hpp"
#include "display.hpp"
#include "testUtilities.hpp"
#include <cstdlib>
#include <vector>

static void	testReserve(int n)
{
	displayHeader("testReserve");

	std::vector<int>	a;
	fillVector(a, n);

	ft::vector<int>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	int newSize;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.reserve(newSize);
	b.reserve(newSize);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.reserve(newSize);
	b.reserve(newSize);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.reserve(newSize);
	b.reserve(newSize);
	check(a, b);
	displayHeader("testReserve End");
}

static void	testResize(int n)
{
	displayHeader("testResize");

	std::vector<int>	a;
	fillVector(a, n);

	ft::vector<int>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	int newSize;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.resize(newSize);
	b.resize(newSize);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.resize(newSize);
	b.resize(newSize);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.resize(newSize);
	b.resize(newSize);
	check(a, b);
	displayHeader("testResize End");
}

template<typename T>
void	checkCapacityOthers(const std::vector<T>& a, const ft::vector<T>& b)
{
	std::cout << std::boolalpha << std::right;
	std::cout << std::setw(30) << "empty " << ": " << (a.empty() == b .empty()) << std::endl;
	std::cout << std::setw(30) << "max_size " << ": " << (a.max_size() == b.max_size()) << std::endl;
	check(a, b);

}

static void	testCapacityOthers(int n)
{
	displayHeader("testCapacityOthers");

	{
		std::vector<int>	a;
		ft::vector<int>		b;
		checkCapacityOthers(a, b);
	}
	std::vector<int>	a;

	fillVector(a, n);
	ft::vector<int>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	int newSize;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.resize(newSize);
	b.resize(newSize);
	checkCapacityOthers(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.resize(newSize);
	b.resize(newSize);
	checkCapacityOthers(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	newSize = std::rand() % MAX_N;
	a.resize(newSize);
	b.resize(newSize);
	checkCapacityOthers(a, b);
	displayHeader("testCapacityOthers End");
}

void	testCapacity(int n)
{
	testReserve(n);
	testResize(n);
	testCapacityOthers(n);
}