#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include <type_traits>

namespace ft
{
	template <class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
	class random_access_iterator
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			Pointer	_ptr;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			random_access_iterator() : _ptr(0)
			{
			}

			random_access_iterator(Pointer ptr) : _ptr(ptr)
			{
			}

			random_access_iterator(const random_access_iterator& src) : _ptr(src._ptr)
			{
			}

			random_access_iterator	&operator=(const random_access_iterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				return *this;
			}

			~random_access_iterator()
			{
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Comparison operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			bool	operator==(const random_access_iterator& rop)
			{
				return _ptr == rop._ptr;
			}

			bool	operator!=(const random_access_iterator& rop)
			{
				return _ptr != rop._ptr;
			}

			bool	operator<(const random_access_iterator& rop)
			{
				return _ptr < rop._ptr;
			}

			bool	operator>(const random_access_iterator& rop)
			{
				return _ptr > rop._ptr;
			}

			bool	operator<=(const random_access_iterator& rop)
			{
				return _ptr <= rop._ptr;
			}

			bool	operator>=(const random_access_iterator& rop)
			{
				return _ptr >= rop._ptr;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Comparison operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			random_access_iterator	operator+(Distance d)
			{
				return random_access_iterator(_ptr + d);
			}

			random_access_iterator	operator-(Distance d)
			{
				return random_access_iterator(_ptr - d);
			}

			random_access_iterator	operator-(const random_access_iterator& rop)
			{
				return random_access_iterator(_ptr - rop._ptr);
			}

			random_access_iterator	&operator+=(Distance d)
			{
				_ptr += d;
				return *this;
			}

			random_access_iterator	&operator-=(Distance d)
			{
				_ptr -= d;
				return *this;
			}

			random_access_iterator	&operator++()
			{
				_ptr++;
				return *this;
			}

			random_access_iterator	operator++(int n)
			{
				random_access_iterator	ret(*this);

				_ptr++;
				return ret;
			}

			random_access_iterator	&operator--()
			{
				_ptr--;
				return *this;
			}

			random_access_iterator	operator--(int n)
			{
				random_access_iterator	ret(*this);

				_ptr--;
				return ret;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			Pointer	operator->()
			{
				return _ptr;
			}

			T	&operator*()
			{
				return *_ptr;
			}

			T	&operator[](Distance n)
			{
				return _ptr[n];
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};
}

#endif