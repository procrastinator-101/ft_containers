#include <iostream>

using namespace std;

class A
{
    public:
        A()
        {
            throw 15;
        };
        ~A() throw(int)
        {
            cout << "dest called" << endl;
            throw 15;
        }
};

void foo ()
{
    cout << "foo" << endl;
    static A s;
    cout << "foo yep" << endl;
}


int main() try
{
    foo();
    return 0;
}
catch (...)
{
    cout << "some error happened" << endl;
}