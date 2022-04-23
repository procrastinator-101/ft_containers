#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			reverse_iterator() : _base()
			{
			}

			explicit	reverse_iterator(iterator_type it) : _base(it)
			{
			}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it._base)
			{
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// base
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			iterator_type	base()const
			{
				return _base;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// base End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			reverse_iterator	operator+(difference_type n) const
			{
				return reverse_iterator(_base - n);
			}

			reverse_iterator	&operator++()
			{
				--_base;
				return *this;
			}

			reverse_iterator  operator++(int)
			{
				reverse_iterator	ret = *this;

				++(*this);
				return ret;
			}

			reverse_iterator	&operator+=(difference_type n)
			{
				_base -= n;
				return *this;
			}

			reverse_iterator	operator-(difference_type n) const
			{
				return reverse_iterator(_base + n);
			}

			reverse_iterator	&operator--()
			{
				++_base;
				return *this;
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator	ret = *this;

				--(*this);
				return ret;
			}

			reverse_iterator	&operator-=(difference_type n)
			{
				_base += n;
				return *this;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			reference	operator*() const
			{
				return *(_base - 1);
			}

			pointer	operator->() const
			{
				return &(operator*());
			}

			reference	operator[] (difference_type n) const
			{
				return *(_base - n - 1);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			iterator_type	_base;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Relational operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class Iterator>
	bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Iterator>
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Relational operators End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif