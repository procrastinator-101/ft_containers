#include <cstdlib>
#include <exception>
#include <iostream>

using namespace std;

void    myTermHandler()
{
    cout << "myTermHandler called" << endl;
    exit(1);
}

void    myExpHandler()
{
    cout << "myExpHadnler called" << endl;
    // myTermHandler();
    // throw ' ';
    throw ;
}

void    foo() throw(char)//, bad_exception)
{
    try 
    {
        throw 0;
    }
    catch (char c)
    {
        cout << "char exception caught" << endl;
    }
    // catch (int n)
    // {
    //     cout << "int exception caught" << endl;
    // }
}

int main()
{
    terminate_handler   term = set_terminate(myTermHandler);
    // term();
    unexpected_handler p = set_unexpected(myExpHandler);
    // p();
    try
    {
        foo();
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    catch (int n)
    {
        cout << "int exception caught" << endl;   
    }
    catch (...)
    {
        cout << "default exception caught" << endl;   
    }
}