#include <iostream>
using namespace std;

template <class X> void swapargs(X &a, X &b)
{
	X temp;
	temp = a;
	a = b;
	b = temp;
	cout << "Inside template swapargs.\n";
}


// Use new-style specialization syntax. accepts swapargs<int>(int, int), swapargs<>(int, int), and swapargs(int, int)
template<>
void swapargs<int>(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
	cout << "Inside swapargs<int> specialization.\n";
}

// This overrides the generic version of swapargs() for ints. accepts swapargs(int, int) only
void swapargs(int &a, int &b)
{
int temp;
  temp = a;
  a = b;
  b = temp;
  cout << "Inside swapargs int specialization.\n";
}

int main()
{
	int i=10, j=20;
	double x=10.1, y=23.3;
	char a='x', b='z';

	cout << "Original i, j: " << i << ' ' << j << '\n';
	cout << "Original x, y: " << x << ' ' << y << '\n';
	cout << "Original a, b: " << a << ' ' << b << '\n';

	swapargs(i, j);
	swapargs<int>(i, j);
	swapargs<>(i, j);
	swapargs(x, y);
	swapargs(a, b);

	cout << "Swapped i, j: " << i << ' ' << j << '\n';
	cout << "Swapped x, y: " << x << ' ' << y << '\n';
	cout << "Swapped a, b: " << a << ' ' << b << '\n';
	return 0;
}