#include <iostream>

using namespace std;

class A
{
    public:
        A() 
        {
            cout << "constor" << endl;
        }
        ~A()
        {
            cout << "dest" << endl;
        }
};


int foo(A s) try
{
    throw 5;
}
catch (int e)
{
    cout << "in" << endl;
    // return e;
    throw ;
}

int main()
{
    A p;

    try
    {
        cout << foo(p) << endl;
    }
    catch (int h)
    {
        cout << "h = " << h << endl;
    }
    cout << "end" << endl;

    return 0;
}