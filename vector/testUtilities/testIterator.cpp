#include "court.hpp"
#include "display.hpp"
#include "testUtilities.hpp"

void	testReverseIter()
{
	std::cout << "//////////////////////// ReverseIter //////////////////////////" << std::endl;
	// bool ret;
	int n = 15;

	std::vector<int>	nums;
	fillVector(nums, n);

	ft::vector<int>		nbs(nums.begin(), nums.end());

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		ft::vector<int>::reverse_iterator it = nbs.rbegin();
		ft::vector<int>::reverse_iterator itend = nbs.rend();
		show(it, itend);
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		std::vector<int>::reverse_iterator it = nums.rbegin();
		std::vector<int>::reverse_iterator itend = nums.rend();
		show(it, itend);
	}
	std::cout << "////////////////////// ReverseIter End ////////////////////////" << std::endl;
}

void	testIter()
{
	std::cout << "/////////////////////////// Iter //////////////////////////////" << std::endl;
	// bool ret;
	int n = 15;

	std::vector<int>	nums;
	fillVector(nums, n);

	ft::vector<int>		nbs(nums.begin(), nums.end());

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		ft::vector<int>::iterator it = nbs.begin();
		ft::vector<int>::iterator itend = nbs.end();
		show(it, itend);
	}
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	{
		std::vector<int>::iterator it = nums.begin();
		std::vector<int>::iterator itend = nums.end();
		show(it, itend);
	}
	std::cout << "///////////////////////// Iter End ////////////////////////////" << std::endl;
}

void	testIterator()
{
	testIter();
	testReverseIter();
}