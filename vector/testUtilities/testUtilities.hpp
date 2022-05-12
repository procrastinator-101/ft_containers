#ifndef TESTUTILITIES_HPP
# define TESTUTILITIES_HPP

#include <vector>
#include <ostream>
#include <iomanip>
#include <iostream>

#include "court.hpp"
#include "display.hpp"
#include "checker.hpp"
#include "../vector.hpp"

#include "../../algorithm/equal.hpp"
#include "../../algorithm/lexicographical_compare.hpp"

void	testErase();
void	testInsert();
void	testIterator();
void	testConstructor();
void	testAssignmentOperator();

void	testCapacity(int n);

void	fillVector(ft::vector<int>& vec, size_t n);
void	fillVector(ft::vector<ft::court>& vec, size_t n);

void	fillVector(std::vector<int>& vec, size_t n);
void	fillVector(std::vector<ft::court>& vec, size_t n);

std::string	ft_itoa(int n);

#endif