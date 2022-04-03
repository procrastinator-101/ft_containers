#ifndef INPUT_ITERATOR_HPP
# define INPUT_ITERATOR_HPP

#include <iterator>
#include <type_traits>

namespace ft
{
	template <class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
	class input_iterator
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef Distance difference_type;
			typedef T value_type;
			typedef Pointer pointer;
			typedef Reference reference;
			typedef std::input_iterator_tag iterator_category;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		protected:
			Pointer	_ptr;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			input_iterator() : _ptr(0)
			{
			}

			input_iterator(Pointer ptr) : _ptr(ptr)
			{
			}

			input_iterator(const input_iterator& src) : _ptr(src._ptr)
			{
			}

			input_iterator	&operator=(const input_iterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				return *this;
			}

			~input_iterator()
			{
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructors, assignment operators, and destructors End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Comparison operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			bool	operator==(const input_iterator& rop) const
			{
				return _ptr == rop._ptr;
			}

			bool	operator!=(const input_iterator& rop) const
			{
				return _ptr != rop._ptr;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Comparison operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			input_iterator	&operator++()
			{
				_ptr++;
				return *this;
			}

			input_iterator	operator++(int n)
			{
				input_iterator	ret(*this);

				_ptr++;
				(void)n;
				return ret;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			Pointer	operator->() const
			{
				return _ptr;
			}

			const T	operator*() const
			{
				return *_ptr;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};
}

#endif