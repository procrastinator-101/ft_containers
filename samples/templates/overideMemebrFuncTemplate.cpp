#include <iostream>

using namespace std;

class Base
{
	public:
	virtual void f(int)
	{
		cout << "base" << endl;
	}
};
struct Derived : Base 
{
    // this member template does not override Base::f
    template <class T>
	void f(T j)
	{
		cout << "temp Derive" << endl;
	}
 
    // non-template member override can call the template:
    void f(int i)
	{
		cout << "over : ";
		f<>(i);
    }
};


struct A {
    template<typename T>
    operator T*(); // conversion to pointer to any type
};
 
// out-of-class definition
template<typename T>
A::operator T*() {return nullptr;}
 
// explicit specialization for char*
template<>
A::operator char*() {return nullptr;}
 
// explicit instantiation
template A::operator void*();

int main()
{
	Base	*ob1 = new Derived();
	Base	*ob2 = new Base();
	Derived inst;

	inst.f(6.2);
	ob1->f(6.3);
	ob2->f(6);
}