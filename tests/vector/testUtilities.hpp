#ifndef TESTUTILITIES_HPP
# define TESTUTILITIES_HPP

#include <vector>
#include <ostream>
#include <iomanip>
#include <iostream>

#include <vector>

#include "court.hpp"
#include "../shared/checker.hpp"
#include "../shared/display.hpp"

#include "../../vector/vector.hpp"


#define MAX_N 100

void	testInsert();
void	testErase(int n);
void	testAssign(int n);
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