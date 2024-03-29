#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

#include <iterator>

# include "../iterator/iterator_traits.hpp"


namespace ft
{
	template <class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	class vectorIterator
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			typedef vectorIterator<const T> vectorConstIterator;
		
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			vectorIterator() : _ptr(0)
			{
			}

			vectorIterator(pointer ptr) : _ptr(ptr)
			{
			}

			vectorIterator(const vectorIterator& src) : _ptr(src._ptr)
			{
			}

			vectorIterator	&operator=(const vectorIterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				return *this;
			}

			~vectorIterator()
			{
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Conversion operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			operator vectorConstIterator() const
			{
				return vectorConstIterator(_ptr);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Conversion operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Relational operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			bool	operator==(const vectorIterator& rop) const
			{
				return _ptr == rop._ptr;
			}

			bool	operator!=(const vectorIterator& rop) const
			{
				return _ptr != rop._ptr;
			}

			bool	operator<(const vectorIterator& rop) const
			{
				return _ptr < rop._ptr;
			}

			bool	operator>(const vectorIterator& rop) const
			{
				return _ptr > rop._ptr;
			}

			bool	operator<=(const vectorIterator& rop) const
			{
				return _ptr <= rop._ptr;
			}

			bool	operator>=(const vectorIterator& rop) const
			{
				return _ptr >= rop._ptr;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Relational operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			vectorIterator	operator+(difference_type d) const
			{
				return vectorIterator(_ptr + d);
			}

			vectorIterator	operator-(difference_type d) const
			{
				return vectorIterator(_ptr - d);
			}

			difference_type	operator-(const vectorIterator& rop) const
			{
				return _ptr - rop._ptr;
			}

			vectorIterator	&operator+=(difference_type d)
			{
				_ptr += d;
				return *this;
			}

			vectorIterator	&operator-=(difference_type d)
			{
				_ptr -= d;
				return *this;
			}

			vectorIterator	&operator++()
			{
				_ptr++;
				return *this;
			}

			vectorIterator	operator++(int n)
			{
				vectorIterator	ret(*this);
				
				(void)n;
				_ptr++;
				return ret;
			}

			vectorIterator	&operator--()
			{
				_ptr--;
				return *this;
			}

			vectorIterator	operator--(int n)
			{
				vectorIterator	ret(*this);

				(void)n;
				_ptr--;
				return ret;
			}

			friend vectorIterator	operator+(difference_type d, const vectorIterator& it)
			{
				return it + d;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			pointer	operator->() const
			{
				return _ptr;
			}

			T	&operator*() const
			{
				return *_ptr;
			}

			T	&operator[](difference_type n) const
			{
				return _ptr[n];
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			pointer	_ptr;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};
}

#endif