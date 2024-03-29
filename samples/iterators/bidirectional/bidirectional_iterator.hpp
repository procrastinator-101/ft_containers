#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include <type_traits>

namespace ft
{
	template <class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
	class bidirectional_iterator
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
			bidirectional_iterator() : _ptr(0)
			{
			}

			bidirectional_iterator(Pointer ptr) : _ptr(ptr)
			{
			}

			bidirectional_iterator(const bidirectional_iterator& src) : _ptr(src._ptr)
			{
			}

			bidirectional_iterator	&operator=(const bidirectional_iterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				return *this;
			}

			~bidirectional_iterator()
			{
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Comparison operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			bool	operator==(const bidirectional_iterator& rop)
			{
				return _ptr == rop._ptr;
			}

			bool	operator!=(const bidirectional_iterator& rop)
			{
				return _ptr != rop._ptr;
			}

			bool	operator<(const bidirectional_iterator& rop)
			{
				return _ptr < rop._ptr;
			}

			bool	operator>(const bidirectional_iterator& rop)
			{
				return _ptr > rop._ptr;
			}

			bool	operator<=(const bidirectional_iterator& rop)
			{
				return _ptr <= rop._ptr;
			}

			bool	operator>=(const bidirectional_iterator& rop)
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
			bidirectional_iterator	operator+(Distance d)
			{
				return bidirectional_iterator(_ptr + d);
			}

			bidirectional_iterator	operator-(Distance d)
			{
				return bidirectional_iterator(_ptr - d);
			}

			bidirectional_iterator	operator-(const bidirectional_iterator& rop)
			{
				return bidirectional_iterator(_ptr - rop._ptr);
			}

			bidirectional_iterator	&operator+=(Distance d)
			{
				_ptr += d;
				return *this;
			}

			bidirectional_iterator	&operator-=(Distance d)
			{
				_ptr -= d;
				return *this;
			}

			bidirectional_iterator	&operator++()
			{
				_ptr++;
				return *this;
			}

			bidirectional_iterator	operator++(int n)
			{
				bidirectional_iterator	ret(*this);

				_ptr++;
				return ret;
			}

			bidirectional_iterator	&operator--()
			{
				_ptr--;
				return *this;
			}

			bidirectional_iterator	operator--(int n)
			{
				bidirectional_iterator	ret(*this);

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