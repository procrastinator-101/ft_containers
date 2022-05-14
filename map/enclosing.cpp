#include <iostream>


namespace ft
{
	template<typename T>
	class Enclosing;

	template<typename T>
	std::ostream &operator<<(std::ostream& ostr, const Enclosing<T>& root);

	template<typename T>
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

		friend std::ostream &operator<<(std::ostream& ostr, const Enclosing<T>& root);
	};

	template<typename T>
	Enclosing<T>::nested::nested()
	{
		std::cout << "constructor" << std::endl;
	}

	template<typename T>
	Enclosing<T>::nested::~nested()
	{
		std::cout << "desstructor" << std::endl;
	}

	template<typename T>
	Enclosing<T>::nested::nested(const nested& src)
	{
		(void)src;
		std::cout << "copy constructor" << std::endl;
		
	}
	template<typename T>
	typename Enclosing<T>::nested	&Enclosing<T>::nested::operator=(const nested& rop)
	{
		(void)rop;
		std::cout << "assign" << std::endl;
	}

	template<typename T>
	std::ostream &operator<<(std::ostream& ostr, const Enclosing<T>& root)
	{
		(void)root;
		ostr << "enclosing" << std::endl;
		return ostr;
	}
}


namespace ft
{
	template<typename T>
	class Foo; // forward declare to make function declaration possible
	
	template<typename T> // declaration
	std::ostream& operator<<(std::ostream&, const Foo<T>&);
	
	template<typename T>
	class Foo {
	public:
		Foo(const T& val) : data(val) {}
	private:
		T data;
	
		// refers to a full specialization for this particular T 
		friend std::ostream& operator<< <> (std::ostream&, const Foo&);
		// note: this relies on template argument deduction in declarations
		// can also specify the template argument with operator<< <T>"
	};
	
	// definition
	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Foo<T>& obj)
	{
		return os << obj.data;
	}
}
 
int main()
{
    ft::Foo<double> obj(1.23);
    std::cout << obj << '\n';
}
