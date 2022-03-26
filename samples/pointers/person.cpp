#include "person.hpp"
#include <string>

person::person(void)
{
    return ;
}

person::person(int Income) : income(Income)
{
    return ;
}

person::person(std::string name) : name(name)
{
    return ;
}

person::person(std::string name, int income) : name(name), income(income)
{
    return ;
}

person::~person(void)
{
    return ;
}

void    person::show(void)
{
    std::cout << this->age << ' ' << this->name << ' ' << this->income << ' ' << this->birthyear << std::endl;
}

void    person::set(int age, std::string name, int income)
{
    this->income = income;
    this->age = age;
    this->name = name;
    this->birthyear = 2021 - age;
}

void    person::hello()
{
    std::cout << "hello !!!" << std::endl;
}