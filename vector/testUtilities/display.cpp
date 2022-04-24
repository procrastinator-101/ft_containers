#include "display.hpp"

std::string	centerString(int width, const std::string& str)
{
    int len = str.length();
    if (width < len)
		return str;

    int diff = width - len;
    int pad1 = diff / 2;
    int pad2 = diff - pad1;
    return std::string(pad1, ' ') + str + std::string(pad2, ' ');
}

void	displayHeader(const std::string& str)
{
	std::cout << "===============================================================" << std::endl;
	std::cout << "||" << centerString(60, str) << "||" << std::endl;
	std::cout << "===============================================================" << std::endl;
}

void	displaySubHeader(const std::string& str)
{
	std::cout << "--------------------------" << std::endl;
	std::cout << str << std::endl;
	std::cout << "--------------------------" << std::endl;
}
