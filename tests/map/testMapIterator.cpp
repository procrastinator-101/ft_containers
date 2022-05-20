#include "./testUtilities.hpp"


void	testEmpties()
{
	displaySubHeader("testEmpties");
	ft::map<int, int>	ftmap;

	typename ft::map<int, int>::iterator it = ftmap.begin();
	typename ft::map<int, int>::iterator ite = ftmap.end();

	checkEqaulity(it, ite, "iterator");

	
	typename ft::map<int, int>::reverse_iterator rit = ftmap.rbegin();
	typename ft::map<int, int>::reverse_iterator rite = ftmap.rend();
	checkEqaulity(rit, rite, "reverse_iterator");
	displaySubHeader("testEmpties End");
}


void	testFullMap(int n)
{
	displaySubHeader("testFullMap");
	std::vector<int>	input;
	fillVector(input, n);

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