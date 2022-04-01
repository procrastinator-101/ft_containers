#include <exception>
#include <iostream>

using namespace std;

void	bar()
{
	throw bad_exception();
}

int main()
{
	try {
	bar();
	} catch (exception& e) {
	cout << e.what() << endl;
	}
	return 0;
}