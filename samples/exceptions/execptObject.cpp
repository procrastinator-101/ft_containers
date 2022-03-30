#include <exception>
#include <iostream>

class ft_exception : public std::exception
{
    public:
        int number;

        ft_exception() : number(0){std::cout << "con" << std::endl;}
        ~ft_exception() throw() {std::cout << "des" << std::endl;}
        const char  *what() const throw()
        {
            return "some chitty luck u have";
        }
};

void    handler()
{
    try
    {
        // ft_exception ex;
        // std::cout << &ex << std::endl;
        // throw ex;
        throw ft_exception();
    }
    catch (ft_exception& e)
    {
        std::cout << e.what() << std::endl;
        e.number = 20;
        std::cout << &e << std::endl;
        throw ;
    }
}

void    standard()
{
    try
    {
        std::cout << "hi" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    standard();
    try
    {
        handler();
    }
    catch (ft_exception& e)
    {
        std::cout << e.what() << std::endl;
        std::cout << &e << std::endl;
    }
    std::cout << "end" << std::endl;
}