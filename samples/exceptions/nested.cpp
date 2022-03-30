#include <exception>
#include <iostream>

using namespace std;

void    allocate()
{
    try
    {
        cout << "try to allocate ptr" << endl;
        int *ptr = new int [5000000000];
        throw 5;
        cout << "successful allocation" << endl;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    catch (int n)
    {
        cout << "int" << endl;
    }
    cout << "some things just work despite how fuckup they are" << endl;
}

int main()
{
    try
    {
        allocate();
    }
    catch (...)
    {
        cout << "what the fuck happened" << endl;
    }
    cout << "the aftermath" << endl;
    return 0;
}