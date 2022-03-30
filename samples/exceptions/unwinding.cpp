#include <exception>
#include <iostream>

using namespace std;

struct A
{
    static int count;
    int n;
    A(int n = A::count++): n(n)
    {
        cout << "A(" << n << ") constructed successfully\n";
    }
    ~A() throw(std::exception)
    {
        std::cout << "A(" << n << ") destroyed\n";
        throw exception();
    }
};

int A::count = 0;

int foo()
{
    throw std::runtime_error("error");
}
 
struct B
{
    A a1, a2, a3;
    B() try : a1(1), a2(foo()), a3(3)
    {
        std::cout << "B constructed successfully\n";
    }
    catch(...)
    {
    	std::cout << "B::B() exiting with exception\n";
    }
    ~B()
    {
        std::cout << "B destroyed\n";
    }
};
 
struct C : A, B
{
    C() try
    {
        std::cout << "C::C() completed successfully\n";
    }
    catch(...)
    {
        std::cout << "C::C() exiting with exception\n";
    }
    ~C()
    {
        std::cout << "C destroyed\n";
    }
};
 
A    bar()
{
    A tmp;
    A tmp2;
    return tmp;
}


int main ()
try
{
    A a = bar();
}
catch (const std::exception& e) {
    std::cout << "main() failed to create C with: " << e.what();
}