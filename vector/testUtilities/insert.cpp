#include "court.hpp"
#include "testUtilities.hpp"
#include <exception>

void	testInsertInt()
{
	std::cout << "///////////////////////// InsertInt ///////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	int n = 6;
	int	position = 5;

	ft::vector<int>		nbs;
	std::vector<int>	nums;

	fillVector(nbs, n);
	fillVector(nums, n);

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nbs.insert(nbs.begin(), 11);
	std::cout << nbs << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nbs.insert(nbs.begin() + position, 55);
	std::cout << nbs << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nbs.insert(nbs.end(), 99);
	std::cout << nbs << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nums.insert(nums.begin(), 11);
	std::cout << nums << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nums.insert(nums.begin() + position, 55);
	std::cout << nums << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	nums.insert(nums.end(), 99);
	std::cout << nums << std::endl;
	std::cout << "////////////////////// InsertInt End //////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

template<typename T, typename U>
static void	insertExcept(T& v, typename T::iterator position, const U val)
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
	std::cout << v << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

void	testInsertCourt()
{
	std::cout << "/////////////////////// InsertCourt ///////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	int n = 5;
	int	position = 5;

	ft::vector<ft::court>		nbs;
	std::vector<ft::court>	nums;

	fillVector(nbs, n);
	fillVector(nums, n);

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	insertExcept(nbs, nbs.begin(), ft::court("first"));
	insertExcept(nbs, nbs.begin() + position, ft::court("middle"));
	insertExcept(nbs, nbs.end(), ft::court("end"));
	nbs.clear();

	insertExcept(nums, nums.begin(), ft::court("first"));
	insertExcept(nums, nums.begin() + position, ft::court("middle"));
	insertExcept(nums, nums.end(), ft::court("end"));
	nums.clear();
	
	std::cout << "///////////////////// InsertCourt End /////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

void	testInsert()
{
	testInsertInt();
	testInsertCourt();
}