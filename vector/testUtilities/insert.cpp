#include "court.hpp"
#include "testUtilities.hpp"
#include <cstdlib>
#include <vector>


static int n = 33; //std::rand() % 10;
static int	position = std::rand() % n;
static int sequenceSize = 10;

template<typename T, typename U>
static void	insertExcept(T& v, typename T::iterator position, const U& val)
{
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	try
	{
		v.insert(position, val);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

template<typename T, typename U>
static void	insertExcept(T& v, typename T::iterator position, int n, const U& val)
{
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	try
	{
		v.insert(position, n, val);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

template<typename T, typename InputIterator>
static void	insertExcept(T& v, typename T::iterator position, InputIterator first, InputIterator last)
{
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	try
	{
		v.insert(position, first, last);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

void	testInsertInt()
{
	displayHeader("testInsertInt");
	std::vector<int>	a;
	fillVector(a, n);

	ft::vector<int>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	a.insert(a.begin(), 11);
	b.insert(b.begin(), 11);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "positon : " << position << std::endl;
	a.insert(a.begin() + position, 55);
	b.insert(b.begin() + position, 55);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	a.insert(a.end(), 99);
	b.insert(b.end(), 99);
	check(a, b);
	displayHeader("testInsertInt End");
}

void	testInsertIntn()
{
	displayHeader("testInsertIntn");
	int ns[3] = {std::rand() % 10, std::rand() % 10, std::rand() % 10};
	int values[3] = {11, 55, 99};

	std::vector<int>	a;
	fillVector(a, n);

	ft::vector<int>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	b.insert(b.begin(), ns[0], values[0]);
	a.insert(a.begin(), ns[0], values[0]);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	b.insert(b.begin() + position, ns[1], values[1]);
	a.insert(a.begin() + position, ns[1], values[1]);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	b.insert(b.end(), ns[2], values[2]);
	a.insert(a.end(), ns[2], values[1]);
	check(a, b);
	displayHeader("testInsertIntn End");
}

void	testInsertIntIter()
{
	displayHeader("testInsertIntIter");
	std::vector<int>	sequence;
	fillVector(sequence, sequenceSize);


	std::vector<int>	a;
	fillVector(a, n);

	ft::vector<int>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	int range[2];
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	range[0] = rand() % sequence.size();
	range[1] = range[0] + rand() % (sequence.size() - range[0]);
	a.insert(a.begin(), sequence.begin() + range[0], sequence.begin() + range[1]);
	b.insert(b.begin(), sequence.begin() + range[0], sequence.begin() + range[1]);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	range[0] = rand() % sequence.size();
	range[1] = range[0] + rand() % (sequence.size() - range[0]);
	a.insert(a.begin() + position, sequence.begin() + range[0], sequence.begin() + range[1]);
	b.insert(b.begin() + position, sequence.begin() + range[0], sequence.begin() + range[1]);
	check(a, b);
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	range[0] = rand() % sequence.size();
	range[1] = range[0] + rand() % (sequence.size() - range[0]);
	a.insert(a.end(), sequence.begin() + range[0], sequence.begin() + range[1]);
	b.insert(b.end(), sequence.begin() + range[0], sequence.begin() + range[1]);
	check(a, b);
	displayHeader("testInsertIntIter End");
}

void	testInsertCourt()
{
	displayHeader("testInsertCourt");
	std::vector<ft::court>	a;

	fillVector(a, n);

	std::vector<ft::court>	b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	insertExcept(b, b.begin(), ft::court("first"));
	insertExcept(a, a.begin(), ft::court("first"));
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;

	insertExcept(b, b.begin() + position, ft::court("middle"));
	insertExcept(a, a.begin() + position, ft::court("middle"));
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	
	insertExcept(b, b.end(), ft::court("end"));
	insertExcept(a, a.end(), ft::court("end"));
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	displayHeader("testInsertCourt End");
}

void	testInsertCourtn()
{
	displayHeader("testInsertCourtn");
	int ns[3] = {std::rand() % 10, std::rand() % 10, std::rand() % 10};
	ft::court values[3] = {ft::court("first"), ft::court("middle"), ft::court("last")};

	std::vector<ft::court>	a;
	fillVector(a, n);

	std::vector<ft::court>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "n = " << ns[0] << std::endl;
	b.insert(b.begin(), ns[0], values[0]);
	a.insert(a.begin(), ns[0], values[0]);
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "n = " << ns[1] << std::endl;
	b.insert(b.begin() + position, ns[1], values[1]);
	a.insert(a.begin() + position, ns[1], values[1]);
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "n = " << ns[2] << std::endl;
	b.insert(b.end(), ns[2], values[2]);
	a.insert(a.end(), ns[2], values[1]);
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	displayHeader("testInsertCourtn End");
}


void	testInsertCourtIter()
{
	displayHeader("testInsertCourtIter");
	std::vector<ft::court>	sequence;
	fillVector(sequence, sequenceSize);


	std::vector<ft::court>	a;
	fillVector(a, n);

	std::vector<ft::court>		b(a.begin(), a.end());

	std::cout << b << std::endl;
	std::cout << a << std::endl;

	std::cout << std::boolalpha;

	check(a, b);

	int range[2];
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	range[0] = rand() % sequence.size();
	range[1] = range[0] + rand() % (sequence.size() - range[0]);
	std::cout << range[0] << " " << range[1] << std::endl;
	a.insert(a.begin(), sequence.begin() + range[0], sequence.begin() + range[1]);
	b.insert(b.begin(), sequence.begin() + range[0], sequence.begin() + range[1]);
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	range[0] = rand() % sequence.size();
	range[1] = range[0] + rand() % (sequence.size() - range[0]);
	std::cout << range[0] << " " << range[1] << std::endl;
	a.insert(a.begin() + position, sequence.begin() + range[0], sequence.begin() + range[1]);
	b.insert(b.begin() + position, sequence.begin() + range[0], sequence.begin() + range[1]);
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	range[0] = rand() % sequence.size();
	range[1] = range[0] + rand() % (sequence.size() - range[0]);
	std::cout << range[0] << " " << range[1] << std::endl;
	a.insert(a.end(), sequence.begin() + range[0], sequence.begin() + range[1]);
	b.insert(b.end(), sequence.begin() + range[0], sequence.begin() + range[1]);
	check(a, b);
	std::cout << b << std::endl;
	std::cout << a << std::endl;
	displayHeader("testInsertCourtIter End");
}

void	testInsert()
{
	testInsertInt();
	testInsertCourt();
	testInsertIntn();
	testInsertCourtn();
	testInsertIntIter();
	testInsertCourtIter();
}