#include <exception>
#include <iostream>

using namespace std;

class A
{
    int nb;
    static int count;
    public:
        A()
        {
            nb = count++;
            cout << "const " << nb << " called" << endl;
        }
        A(const A& src)
        {
            nb = count++;
            cout << "copy const " << nb << " called" << endl;
        }
        ~A()
        {
            count--;
            cout << "dest " << nb << " called" << endl;
            cout << uncaught_exception() << endl;
            cout << uncaught_exceptions() << endl;
        }
};

int A::count = 0;

int main()
{
    try {
        A t;
    throw A();
    } catch (A a) {
    cout << "ok" << endl;
    }
}