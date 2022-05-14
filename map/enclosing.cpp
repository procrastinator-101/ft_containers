
namespace ft
{
	template<typename T, typename U, typename V>
	class Enclosing
	{
		private:
			class nested
			{
				public:
					class superNested
					{
						public:
							T	a;
					};
				public:
					nested();
					nested(const nested& src);
					nested	&operator=(const nested& rop);
					~nested();
			};
		public:
		void	echo() const
		{
			nested	tmp;
			(void)tmp;
		}
	};

	template<typename T, typename U, typename V>
	Enclosing<T, U, V>::nested::nested()
	{
		std::cout << "constructor" << std::endl;
	}

	template<typename T, typename U, typename V>
	Enclosing<T, U, V>::nested::~nested()
	{
		std::cout << "desstructor" << std::endl;
	}

	template<typename T, typename U, typename V>
	Enclosing<T, U, V>::nested::nested(const nested& src)
	{
		(void)src;
		std::cout << "copy constructor" << std::endl;
		
	}
	template<typename T, typename U, typename V>
	typename Enclosing<T, U, V>::nested	&Enclosing<T, U, V>::nested::operator=(const nested& rop)
	{
		(void)rop;
		std::cout << "assign" << std::endl;
	}
}