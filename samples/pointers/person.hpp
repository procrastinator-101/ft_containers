#ifndef PERSON_HPP
# define PERSON_HPP

# include <string>
# include <iostream>
class person
{
    int income;

public :
    static int  race;
    int         age;
    int         birthyear;
    std::string name;
    double      s;

    person(void);
    person(int Income);
    person(std::string name);
    person(std::string name, int income);
    ~person(void);
    // virtual void	show();
    // virtual void	set(int age, std::string name, int income);
    void	show();
    void	set(int age, std::string name, int income);
    static void hello();
};

class alpha : public person
{
    public:
    void    show()
    {
        std::cout << "alpha" << std::endl;
    }
    void	set(int age, std::string name, int income)
    {
        std::cout << "alpha" << std::endl;
    }    
};

#endif
