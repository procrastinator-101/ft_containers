#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <ostream>
#include <vector>
#include <iostream>

void		displayHeader(const std::string& str);
void		displaySubHeader(const std::string& str);
std::string	centerString(int width, const std::string& str);

#endif