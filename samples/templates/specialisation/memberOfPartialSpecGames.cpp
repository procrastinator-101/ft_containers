#include <iostream>

using namespace std;

template<class T> struct A // enclosing class template
{
    template<class T2>
    struct B {};      // primary member template
    template<class T2>
    struct B<T2*> {}; // partial specialization of member template
};
 
template<>
template<class T2>
struct A<short>::B {}; // full specialization of primary member template
                       // (will ignore the partial)
 
A<char>::B<int*> abcip;  // uses partial specialization T2=int
A<short>::B<int*> absip; // uses full specialization of the primary (ignores partial)
A<char>::B<int> abci;    // uses primary