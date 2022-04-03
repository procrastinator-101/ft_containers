#include <istream>
#include <iterator>
#include <iostream>

int main()
{
	std::istream_iterator<int>	ist(std::cin);
	std::istream_iterator<int>	end;

	std::istream_iterator<int>	clone(ist);

	while (ist != end)
	{
		for (int i = 0; i < 5; i++)
			std::cout << *ist << " ";
		std::cout << "|";
		for (int i = 0; i < 5; i++)
			std::cout << *clone << " ";//ok
		std::cout << "|";
		++ist;
		clone++;//mess things up
	}

	return 0;
}