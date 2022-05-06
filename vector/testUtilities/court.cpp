#include "court.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>


#define STRSIZE 6
#define MAXCOUNT 10000

namespace ft
{
	int court::count = 0;

	court::court() : _str(0)
	{
		count++;
		std::cout << "Default constructor : " << count << std::endl;
		checkMaxCount();
		_buildStr();
	}

	court::~court()
	{
		std::cout << "Default destructor : " << count << " " << _name << std::endl;
		count--;
		_destroyStr();
	}

	court::court(const std::string& name) : _name(name), _str(0)
	{
		count++;
		std::cout << "Parameterised constructor : " << count << " " << _name << std::endl;
		checkMaxCount();
		_buildStr();
	}

	court::court(const court& src) : _name(src._name), _str(0)
	{
		count++;
		std::cout << "Copy constructor : " << count << " " << _name << std::endl;
		checkMaxCount();
		_buildStr();
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
		if (count > MAXCOUNT)
		{
			count--;
			throw std::logic_error("Max count reached");
		}
	}

	void	court::_buildStr()
	{
		_str = new char[STRSIZE];
		::memmove(_str, "hello", STRSIZE);
	}

	void	court::_destroyStr()
	{
		delete [] _str;
	}

	bool	operator==(const court& lhs, const court& rhs)
	{
		// std::cout << "comp" << std::endl;
		// std::cout << lhs._name << " | " << rhs._name << std::endl;
		// bool ret = lhs._name == rhs._name && !strcmp(lhs._str, rhs._str);
		// std::cout << "comp2" << std::endl;
		// return ret;
		return lhs._name == rhs._name && !strcmp(lhs._str, rhs._str);
	}

	bool	operator!=(const court& lhs, const court& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const court& lhs, const court& rhs)
	{
		return lhs._name < rhs._name && strcmp(lhs._str, rhs._str) < 0;
	}

	bool operator>(const court& lhs, const court& rhs)
	{
		return rhs < lhs;
	}

	bool operator<=(const court& lhs, const court& rhs)
	{
		return !(rhs < lhs);
	}

	bool operator>=(const court& lhs, const court& rhs)
	{
		return !(lhs < rhs);
	}
}

std::ostream	&operator<<(std::ostream& ostr, const ft::court& c)
{
	ostr << c.getName();
	return ostr;
}