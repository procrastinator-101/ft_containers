#include <iostream>

using namespace std;

class enclose 
{
    typedef int myint;
    struct nested { // private member
        void g() {cout << "hola" << endl;}
    };
 public:
    static nested f() { return nested(); }
};
 
int main()
{
    //enclose::nested n1 = enclose::f(); // error: 'nested' is private
 
    enclose::f().g(); // OK: does not name 'nested'
    
    int n = 5;
    cout << typeid(enclose::f()).name() << endl;;
}
