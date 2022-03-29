#include <iostream>
using namespace std;

class X
{
    int a;

    public:
        template<class T>
        X(T src)
        {
            cout << "templated" << endl;
        }
        int geta() { return a; }
};


void    foo(X x)
{
    cout << x.geta() << endl;
}

int main()
{
    X ob = 99;

    X s(ob);
    cout << ob.geta();
    // foo(X(10, 15));
    return 0;
}