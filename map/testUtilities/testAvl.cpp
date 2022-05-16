#include "testUtilities.hpp"



int main(int argc, char **argv)
{
	int		n;
	std::vector<int>	numbers;

	srand(time(0));
	if (argc == 2)
		n = std::atoi(argv[1]);
	else
		n = std::rand() % 100;
	for (int i = 0; i < n; i++)
		numbers.push_back(std::rand());

	// testInsertDelete(numbers);

	testAvlIterator(n);
	return 0;
}