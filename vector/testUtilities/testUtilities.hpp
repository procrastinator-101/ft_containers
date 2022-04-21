#ifndef TESTUTILITIES_HPP
# define TESTUTILITIES_HPP

#include <vector>
#include <ostream>
#include <iomanip>
#include <iostream>

#include "court.hpp"
#include "display.hpp"
#include "../vector.hpp"

void	testInsert();
void	testConstructor();

void	fillVector(ft::vector<int>& vec, size_t n);
void	fillVector(ft::vector<ft::court>& vec, size_t n);

void	fillVector(std::vector<int>& vec, size_t n);
void	fillVector(std::vector<ft::court>& vec, size_t n);

#endif