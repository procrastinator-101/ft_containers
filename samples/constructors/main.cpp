#include <iostream>
using namespace std;

class X
{
    int a;

    public:
        X(int j)
        {
            a = j;
            cout << "par" << endl;
        }
        X(int j, int c)
        {
            a = j;
            cout << "par" << endl;
        }
        X(const X& src) : a(src.a)
        {
            cout << "copy" << endl;
        }
        int geta() { return a; }
};


void    foo(X x)
{
    cout << x.geta() << endl;
}

int main()
{
    X ob = 99; // passes 99 to j
    cout << ob.geta(); // outputs 99
    foo(X(10, 15));
    return 0;
}