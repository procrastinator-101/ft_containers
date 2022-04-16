#include <vector>

#include "vector.hpp"


void	printVector(const std::vector<int>& vec)
{
	std::cout << "======================= STD ==========================" << std::endl;
	std::cout << "======================= data =========================" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
	std::cout << "===================== capacity =======================" << std::endl;
	std::cout << "max  = " << vec.max_size() << std::endl;
	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "cap  = " << vec.capacity() << std::endl;
	std::cout << "======================================================" << std::endl;

}

void	printVector(const ft::vector<int>& vec)
{
	std::cout << "======================== FT ==========================" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
	std::cout << "===================== capacity =======================" << std::endl;
	std::cout << "max  = " << vec.max_size() << std::endl;
	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "cap  = " << vec.capacity() << std::endl;
	std::cout << "======================================================" << std::endl;
}

void	fillVector(std::vector<int>& vec, size_t n)
{
	for (size_t i = 0; i < n; i++)
		vec.push_back(std::rand() % n + 100);
}

void	fillVector(ft::vector<int>& vec, size_t n)
{
	for (size_t i = 0; i < n; i++)
		vec.push_back(std::rand() % n + 100);
}

template<typename INPUT_ITERATOR>
void	show(INPUT_ITERATOR first, INPUT_ITERATOR last)
{
	std::cout << "======================= Show =========================" << std::endl;
	while (first != last)
	{
		std::cout << *first << " ";
		++first;
	}
	std::cout << std::endl;
	std::cout << "======================================================" << std::endl;
}

void	testVector()
{
	int n = 19;

	ft::vector<int>		nbs;
	std::vector<int>	nums;

	fillVector(nbs, n);
	fillVector(nums, n);

	printVector(nbs);
	printVector(nums);

	show(nbs.begin(), nbs.end());
	show(nums.begin(), nums.end());
	

	std::vector<int>::const_iterator	it = nums.begin();
	ft::vector<int>::const_iterator		it2 = nbs.begin();

	show(it, static_cast<std::vector<int>::const_iterator>(nums.end()));
	show(it2, static_cast<ft::vector<int>::const_iterator>(nbs.end()));
	
	std::cout << (typeid(std::iterator_traits<int *>::pointer) == typeid(int *)) << std::endl;
	std::cout << (typeid(ft::iterator_traits<int *>::pointer) == typeid(int *)) << std::endl;
}