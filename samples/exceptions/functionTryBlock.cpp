#include <iostream>

using namespace std;

class A
{
    public:
        A() try
        {
            throw 15;
        }
        catch (int n)
        {
            cout << n << endl;
            // return;  illegal
        }
        // A() 
        // {
        //     try
        //     {
        //         int a;
        //     }
        //     catch (int j)
        //     {
        //         return; legal
        //     }
        // }
        ~A() try
        {
            throw 15;
        }
        catch (int n)
        {
            cout << n << endl;
            return; //legal
        }
};


int foo(int s) try
{
    throw s;
}
catch (int e)
{
    return e * s;
}

int main()
{
    cout << foo(2) << endl;

    A a;
    return 0;
}