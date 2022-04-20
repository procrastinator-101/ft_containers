#ifndef COURT_HPP
# define COURT_HPP

#include <stdexcept>
#include <string>

namespace ft
{
	class court
	{
		private:
			static int	count;
			std::string	_name;
			char	*_str;

			void	checkMaxCount() const;
			void	_buildStr();
			void	_destroyStr();

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

}
std::ostream	&operator<<(std::ostream& ostr, const ft::court& c);


#endif