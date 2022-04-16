// sample2.C
template <typename T, T val>
struct A
{
    virtual T foo();
    virtual T bar();
};

extern template int A<int,55>::foo();

template <class T, T val>
T A<T,val>::foo(void)
{
    return val;
}

template <class T, T val>
T A<T,val>::bar(void)
{
    return val;
}

int main(void)
{
    return A<int,55>().bar();
}