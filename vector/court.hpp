#ifndef COURT_HPP
# define COURT_HPP

#include <stdexcept>
#include <string>

class court
{
	static int	count;
	std::string	_name;

		void	checkMaxCount() const;

	public:
		court();
		~court();

		court(const std::string& name);
		court(const court& src);
		court	&operator=(const court& rop);

		static int	getCount();
		std::string	getName() const;
		void	setName(const std::string& name);
};

#endif