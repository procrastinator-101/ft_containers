#include "court.hpp"
#include "testUtilities.hpp"
#include <algorithm>
#include <ios>

static int n = 10;
static int end = 6;
static int start = 0;
static int	position = 8;


void	testEraseInt()
{
	std::cout << "///////////////////////// EraseInt ////////////////////////////" << std::endl;

	bool ret;
	std::vector<int>	nums;
	fillVector(nums, n);

	ft::vector<int>		nbs(nums.begin(), nums.end());

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	std::cout << std::boolalpha;

	ret = ft::equal(nums.begin(), nums.end(), nbs.begin());
	std::cout << "nums == nbs : " << ret << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nbs.erase(nbs.begin() + position);
	nums.erase(nums.begin() + position);
	ret = ft::equal(nums.begin(), nums.end(), nbs.begin());
	std::cout << "nums == nbs : " << ret << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nbs.erase(nbs.begin() + start, nbs.begin() + end);
	nums.erase(nums.begin() + start, nums.begin() + end);
	ret = ft::equal(nums.begin(), nums.end(), nbs.begin());
	std::cout << "nums == nbs : " << ret << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;
	std::cout << "////////////////////// EraseInt End ///////////////////////////" << std::endl << std::endl;
}

void	testEraseCourt()
{
	std::cout << "/////////////////////// EraseCourt ////////////////////////////" << std::endl;

	bool ret;
	std::vector<ft::court>	nums;

	fillVector(nums, n);

	ft::vector<ft::court>	nbs(nums.begin(), nums.end());

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	std::cout << std::boolalpha;

	ret = ft::equal(nums.begin(), nums.end(), nbs.begin());
	std::cout << "nums == nbs : " << ret << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nbs.erase(nbs.begin() + position);
	nums.erase(nums.begin() + position);
	ret = ft::equal(nums.begin(), nums.end(), nbs.begin());
	std::cout << "nums == nbs : " << ret << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nbs.erase(nbs.begin() + start, nbs.begin() + end);
	nums.erase(nums.begin() + start, nums.begin() + end);
	ret = ft::equal(nums.begin(), nums.end(), nbs.begin());
	std::cout << "nums == nbs : " << ret << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;
	std::cout << "///////////////////// EraseCourt End //////////////////////////" << std::endl << std::endl; ;
}

void	testErase()
{
	testEraseInt();
	testEraseCourt();
}