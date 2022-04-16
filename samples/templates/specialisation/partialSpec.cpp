#include <iostream>

using namespace std;

template <typename T, typename U>
void	show(T s, U del, int size)
{
	cout << s << del << size << endl;
}

template<class T1, class T2, class T3 = int>
class A
{
	public:
	A()
	{
		cout << "template" << endl;
	}
};             // primary template

template<class T1, class T2, class T3>
class A<T1*, T2*, T3>
{
	public:
	A()
	{
		cout << "spec" << endl;
		cout << typeid(T3).name() << endl;
	}
};

int main()
{
	string name("younes");
	show("abc", ' ', 15);
	show(string("5863"), '|', 62);
	show(15, 98, 2);
	show(15, 'o', 2);
	show<>(name, 'o', 2);
	show<>('p', 'o', 2);
	A<int, int, char> p;
	A<int*, char*> p2;
	return 0;
}