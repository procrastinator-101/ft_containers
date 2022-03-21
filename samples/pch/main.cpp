#include "header.hpp"
#include <typeinfo>



struct parent
{
    virtual ~parent(){}

};

struct child : public parent
{};

int main()
{
    std::vector<int> numbers;

    for (int i = 0; i < 10; i++)
        numbers.push_back(std::rand() % 200);
    
    for (int i = 0; i < 10; i++)
        std::cout << numbers[i] << " ";
    std::cout << std::endl;
    return 0;
}