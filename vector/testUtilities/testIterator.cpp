#include "court.hpp"
#include "display.hpp"
#include "testUtilities.hpp"

template<typename T>
void	testReverseIter(int n)
{
	displayHeader("testReverseIter");

	std::vector<T>	nums;
	fillVector(nums, n);

	ft::vector<T>		nbs(nums.begin(), nums.end());

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		typename ft::vector<T>::reverse_iterator it = nbs.rbegin();
		typename ft::vector<T>::reverse_iterator itend = nbs.rend();
		show(it, itend);
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		typename std::vector<T>::reverse_iterator it = nums.rbegin();
		typename std::vector<T>::reverse_iterator itend = nums.rend();
		show(it, itend);
	}
	displayHeader("testReverseIter End");
}

template<typename T>
void	testIter(int n)
{
	displayHeader("testReverseIter");

	std::vector<T>	nums;
	fillVector(nums, n);

	ft::vector<T>		nbs(nums.begin(), nums.end());

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		typename ft::vector<T>::iterator it = nbs.begin();
		typename ft::vector<T>::iterator itend = nbs.end();
		show(it, itend);
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		typename std::vector<T>::iterator it = nums.begin();
		typename std::vector<T>::iterator itend = nums.end();
		show(it, itend);
	}
	displayHeader("testReverseIter End");
}

void	testIterator()
{
	testIter<int>(15);
	testReverseIter<int>(15);
	testIter<ft::court>(15);
	testReverseIter<ft::court>(15);
}