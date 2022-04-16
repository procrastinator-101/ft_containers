#include "court.hpp"
#include <iostream>
#include <stdexcept>

int court::count = 0;

court::court()
{
	count++;
	std::cout << "Default constructor : " << count << std::endl;
	checkMaxCount();
}

court::~court()
{
	std::cout << "Default destructor : " << count << std::endl;
	count--;
}

court::court(const std::string& name) : _name(name)
{
	count++;
	std::cout << "Parameterised constructor : " << count << std::endl;
	checkMaxCount();
}

court::court(const court& src) : _name(src._name)
{
	count++;
	std::cout << "Copy constructor : " << count << std::endl;
	checkMaxCount();
}

court	&court::operator=(const court& rop)
{
	std::cout << "Assignment operator" << std::endl;
	if (this == &rop)
		return *this;
	_name = rop._name;
	return *this;
}

std::string	court::getName() const
{
	return _name;
}

int		court::getCount()
{
	return count;
}

void	court::setName(const std::string& name)
{
	_name = name;
}

void	court::checkMaxCount() const
{
	if (count > 4)
	{
		count--;
		throw std::logic_error("Max count reached");
	}
}