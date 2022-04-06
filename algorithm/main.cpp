// equal algorithm example
#include <iostream>     // std::cout
#include <vector>       // std::vector

#include "equal.hpp"

bool mypredicate (int i, int j)
{
	return (i==j);
}

void	testEqual()
{
	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( ft::equal(myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using default comparison:
	if ( ft::equal(myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	// using predicate comparison:
	if ( ft::equal(myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";
}

bool mycomp (char c1, char c2)
{
	return std::tolower(c1) < std::tolower(c2);
}

void	testLexCompare()
{
	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << std::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';
}

int main ()
{
	std::cout << "============================================================" << std::endl;
	testEqual();
	std::cout << "============================================================" << std::endl;
	testLexCompare();
	std::cout << "============================================================" << std::endl;
	return 0;
}