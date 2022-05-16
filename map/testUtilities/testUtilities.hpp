#ifndef TESTUTILITIES_HPP
# define TESTUTILITIES_HPP

#include "../avl.hpp"
#include <cstdlib>
#include <functional>
#include <memory>
#include <sys/_types/_size_t.h>
#include <vector>

void	testAvlIterator(int n);
void	testInsertDelete(std::vector<int>& numbers);

#endif