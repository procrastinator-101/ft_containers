#include "court.hpp"
#include "testUtilities.hpp"


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
	std::cout << v << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

template<typename T, typename U>
static void	insertExcept(T& v, typename T::iterator position, int n, const U& val)
{
	std::cout << "insert : " << n << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	try
	{
		v.insert(position, n, val);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << v << std::endl;
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
	std::cout << v << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

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


void	testInsertCourt()
{
	std::cout << "/////////////////////// InsertCourt ///////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	int n = 5;
	int	position = 4;

	ft::vector<ft::court>		nbs;
	std::vector<ft::court>	nums;

	fillVector(nbs, n);
	std::cout << nbs << std::endl;
	insertExcept(nbs, nbs.begin(), ft::court("first"));
	insertExcept(nbs, nbs.begin() + position, ft::court("middle"));
	insertExcept(nbs, nbs.end(), ft::court("end"));
	nbs.clear();

	fillVector(nums, n);
	std::cout << nums << std::endl;
	insertExcept(nums, nums.begin(), ft::court("first"));
	insertExcept(nums, nums.begin() + position, ft::court("middle"));
	insertExcept(nums, nums.end(), ft::court("end"));
	nums.clear();
	
	std::cout << "///////////////////// InsertCourt End /////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

// void	testInsertIntn()
// {
// 	std::cout << "///////////////////////// InsertIntn //////////////////////////" << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	int size = 6;
// 	int ns[3] = {std::rand() % 10, std::rand() % 10, std::rand() % 10};
// 	int values[3] = {11, 55, 99};
// 	int	position = 5;

// 	ft::vector<int>		nbs;
// 	std::vector<int>	nums;

// 	fillVector(nbs, size);
// 	fillVector(nums, size);

// 	std::cout << nbs << std::endl;
// 	std::cout << nums << std::endl;

// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	nbs.insert(nbs.begin(), ns[0], values[0]);
// 	std::cout << nbs << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	nbs.insert(nbs.begin() + position, ns[1], values[1]);
// 	std::cout << nbs << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	nbs.insert(nbs.end(), ns[2], values[2]);
// 	std::cout << nbs << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	nums.insert(nums.begin(), ns[0], values[0]);
// 	std::cout << nums << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	nums.insert(nums.begin() + position, ns[1], 55);
// 	std::cout << nums << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	nums.insert(nums.end(), ns[2], 99);
// 	std::cout << nums << std::endl;
// 	std::cout << "////////////////////// InsertIntn End /////////////////////////" << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// }


// void	testInsertCourtn()
// {
// 	std::cout << "/////////////////////// InsertCourtn //////////////////////////" << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// 	int size = 4;
// 	int ns[3] = {std::rand() % 10, std::rand() % 10, std::rand() % 10};
// 	int	position = 4;

// 	ft::vector<ft::court>		nbs;
// 	std::vector<ft::court>	nums;

// 	fillVector(nbs, size);
// 	std::cout << nbs << std::endl;
// 	insertExcept(nbs, nbs.begin(), ns[0], ft::court("first"));
// 	insertExcept(nbs, nbs.begin() + position, ns[1], ft::court("middle"));
// 	insertExcept(nbs, nbs.end(), ns[2], ft::court("end"));
// 	nbs.clear();

// 	fillVector(nums, size);
// 	std::cout << nums << std::endl;
// 	insertExcept(nums, nums.begin(), ns[0], ft::court("first"));
// 	insertExcept(nums, nums.begin() + position, ns[1], ft::court("middle"));
// 	insertExcept(nums, nums.end(), ns[2], ft::court("end"));
// 	nums.clear();
	
// 	std::cout << "///////////////////// InsertCourtn End ////////////////////////" << std::endl;
// 	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
// }

void	testInsertIntIter()
{
	std::cout << "/////////////////////// InsertIntIter /////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	int n = 6;
	int	position = 5;
	int	ranges[3][2] = {{2, 5}, {7, 14}, {19, 20}};

	int src[20];
	for (int i = 0; i < 20; i++)
		src[i] = std::rand() % 20;
	for (int i = 0; i < 20; i++)
		std::cout << std::setw(3) << i << " ";
	std::cout << std::endl;
	for (int i = 0; i < 20; i++)
		std::cout << std::setw(3) << src[i] << " ";
	std::cout << std::endl;

	ft::vector<int>		nbs;
	std::vector<int>	nums;

	fillVector(nbs, n);
	fillVector(nums, n);

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	insertExcept(nbs, nbs.begin(), src + ranges[0][0], src + ranges[0][1]);
	insertExcept(nbs, nbs.begin() + position, src + ranges[1][0], src + ranges[1][1]);
	insertExcept(nbs, nbs.end(), src + ranges[2][0], src + ranges[2][1]);

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	
	insertExcept(nums, nums.begin(), src + ranges[0][0], src + ranges[0][1]);
	insertExcept(nums, nums.begin() + position, src + ranges[1][0], src + ranges[1][1]);
	insertExcept(nums, nums.end(), src + ranges[2][0], src + ranges[2][1]);

	std::cout << "//////////////////// InsertIntIter End ////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}


void	testInsertCourtIter()
{
	std::cout << "////////////////////// InsertCourtIter ////////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	int n = 3;
	int	position = 1;
	int	ranges[3][2] = {{2, 5}, {7, 14}, {19, 20}};

	ft::court src[20];
	for (int i = 0; i < 20; i++)
		src[i] = std::string("|name ") + std::to_string(std::rand() % 26) + "|";

	ft::vector<ft::court>		nbs;
	std::vector<ft::court>	nums;

	fillVector(nbs, n);
	fillVector(nums, n);

	std::cout << nbs << std::endl;
	std::cout << nums << std::endl;

	insertExcept(nbs, nbs.begin(), src + ranges[0][0], src + ranges[0][1]);
	insertExcept(nbs, nbs.begin() + position, src + ranges[1][0], src + ranges[1][1]);
	insertExcept(nbs, nbs.end(), src + ranges[2][0], src + ranges[2][1]);

	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
	
	insertExcept(nums, nums.begin(), src + ranges[0][0], src + ranges[0][1]);
	insertExcept(nums, nums.begin() + position, src + ranges[1][0], src + ranges[1][1]);
	insertExcept(nums, nums.end(), src + ranges[2][0], src + ranges[2][1]);

	std::cout << "//////////////////// InsertCourtIter End //////////////////////" << std::endl;
	std::cout << "///////////////////////////////////////////////////////////////" << std::endl;
}

void	testInsert()
{
	// testInsertInt();
	// testInsertCourt();
	// testInsertIntn();
	// testInsertCourtn();
	// testInsertIntIter();
	testInsertCourtIter();
}