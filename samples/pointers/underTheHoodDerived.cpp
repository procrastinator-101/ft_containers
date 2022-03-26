#include "person.hpp"
#include <cstring>
#include <iostream>
#include <string>
#include <sys/_types/_size_t.h>

int main()
{
	alpha someone;
	int		alpha::*prace;
	int		alpha::*pincome;
	int		alpha::*page;
	int		alpha::*pbirthyear;
	double	alpha::*ps;
	std::string	alpha::*pname;

	void	(alpha::*pshow)();
	void	(alpha::*pset)(int, std::string, int);
	void	(alpha::*phello)(void);

	// pincome = &alpha::income;
	// prace = &alpha::race;
	page = &alpha::age;
	pbirthyear = &alpha::birthyear;
	pname = &alpha::name;
	ps = &alpha::s;

	pshow = &alpha::show;
	pset = &alpha::set;

	std::cout << "sizeof(pincome) = " << sizeof(pincome) << std::endl;
	std::cout << "sizeof(page) = " << sizeof(page) << std::endl;
	std::cout << "sizeof(pbirthyear) = " << sizeof(pbirthyear) << std::endl;
	std::cout << "sizeof(ps) = " << sizeof(ps) << std::endl;
	std::cout << "sizeof(pname) = " << sizeof(pname) << std::endl;
	std::cout << "sizeof(pshow) = " << sizeof(pshow) << std::endl;
	std::cout << "sizeof(pset) = " << sizeof(pset) << std::endl;

	size_t	holder = 0;
	// memmove(&holder, &pincome, sizeof(pincome));
	// std::cout << "pincome = " << holder << std::endl;

	memmove(&holder, &page, sizeof(page));
	std::cout << "page = " << holder << std::endl;

	memmove(&holder, &pbirthyear, sizeof(pbirthyear));
	std::cout << "pbirthyear = " << holder << std::endl;

	memmove(&holder, &ps, sizeof(ps));
	std::cout << "ps = " << holder << std::endl;

	memmove(&holder, &pname, sizeof(pname));
	std::cout << "pname = " << holder << std::endl;

	char buf[16];
	memmove(buf, &pshow, sizeof(pshow));
	std::cout << "pshow = " << std::hex << *((size_t *)buf) << " " << *(((size_t *)buf) + 1) << std::endl;

	memmove(buf, &pset, sizeof(pset));
	std::cout << "pset = " << std::hex << *((size_t *)buf) << " " << *(((size_t *)buf) + 1) << std::endl;

	void	(person::*tmp)(void);

	tmp = &person::show;
	memmove(&holder, &tmp, sizeof(page));
	std::cout << "page = " << holder << std::endl;
	return 0;
}