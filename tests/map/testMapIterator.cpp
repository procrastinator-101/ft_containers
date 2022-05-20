#include "testUtilities.hpp"
#include <sys/_types/_size_t.h>


void	testEmpties()
{
	displaySubHeader("testEmpties");
	ft::map<int, int>	ftmap;

	ft::map<int, int>::iterator it = ftmap.begin();
	ft::map<int, int>::iterator ite = ftmap.end();

	checkEqaulity(it, ite, "iterator");

	
	ft::map<int, int>::reverse_iterator rit = ftmap.rbegin();
	ft::map<int, int>::reverse_iterator rite = ftmap.rend();
	checkEqaulity(rit, rite, "reverse_iterator");
	displaySubHeader("testEmpties End");
}


void	testFullMap(size_t n)
{
	displaySubHeader("testFullMap");
	int val;
	std::vector<ft::pair<const int, int> >	input;
	for (size_t i = 0; i < n; i++)
	{
		val = std::rand() % n + 100;
		input.push_back(ft::make_pair(val, val));
	}

	//create two map with the input vector
	std::map<int, int>	stdmap(input.begin(), input.end());
	ft::map<int, int>	ftmap(input.begin(), input.end());

	//check equality
	checkMap(stdmap, ftmap);
	displaySubHeader("testFullMap End");
}

void	testMapIterator(int n)
{
	displayHeader("testMapIterator");
	testEmpties();
	testFullMap(n);
	displayHeader("testMapIterator End");
}