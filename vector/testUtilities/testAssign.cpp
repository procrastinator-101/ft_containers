#include "court.hpp"
#include "testUtilities.hpp"
#include <cstdlib>
#include <sys/_types/_size_t.h>
#include <vector>

static int fill = 1;

template<typename T, typename U>
static void	assignExcept(T& v, size_t size, const U& val)
{
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	try
	{
		v.assign(size, val);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

template<typename T, typename InputIterator>
static void	assignExcept(T& v, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
{
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	try
	{
		v.assign(first, last);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

template<typename T>
void	testAssignFill(int n, int size, const T& val)
{
	displayHeader("testAssignFill");
	std::vector<T>	sequence;
	if (fill)
		fillVector(sequence, n);
	
	std::vector<T>	a;
	if (fill)
		fillVector(a, n);

	ft::vector<T>		b(a.begin(), a.end());

	std::cout << std::boolalpha;

	check(a, b);
	std::cout << "size : " << size << " n : " << n << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	assignExcept(a, size, val);
	assignExcept(b, size, val);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	assignExcept(a, size, val);
	assignExcept(b, size, val);
	check(a, b);
	displayHeader("testAssignFill End");
}

template<typename T>
void	testAssignRange(int n, int size)
{
	displayHeader("testAssignRange");
	std::vector<T>	sequence;
	if (fill)
		fillVector(sequence, size);
	
	std::vector<T>	a;
	if (fill)
		fillVector(a, n);

	ft::vector<T>		b(a.begin(), a.end());

	std::cout << std::boolalpha;

	check(a, b);

	std::cout << "size : " << size << " n : " << n << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	assignExcept(b, sequence.begin(), sequence.end());
	assignExcept(a, sequence.begin(), sequence.end());
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	assignExcept(a, sequence.begin(), sequence.end());
	assignExcept(b, sequence.begin(), sequence.end());
	check(a, b);
	displayHeader("testAssignRange End");
}

void	testAssign(int n)
{
	int size;

	// n = 10;
	size = 40;
	size = std::rand() % MAX_N;
	testAssignFill(n, size, 15);
	testAssignFill(n, size, ft::court(std::string("|name ") + ft_itoa(std::rand() % 26) + "|"));
	testAssignRange<int>(n, size);
	testAssignRange<ft::court>(n, size);
}