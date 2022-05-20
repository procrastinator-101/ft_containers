#include "testUtilities.hpp"

void	testVector()
{
	int n = std::rand() % 100;
	testConstructor();
	testAssignmentOperator();
	testIterator();
	testInsert();
	testCapacity(n);
	testAssign(n);
	testErase(n);
}