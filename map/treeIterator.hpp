#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

#include <iterator>

namespace ft
{
	/**
	 * @brief an iterator that iterates through a tree having NodeType as its
	 		  node type
	 * 
	 * @tparam T :	the value type of the node
	 * @tparam NodeType : it is expected to have at least a public value attribute,
	 					  getInOrderSuccessor and getInOrderPredeccessor methods.
						  the constructor expects a last argument which points to the
						  address of the last node pointer in the tree.
	 */

	template<typename T, template<typename> class NodeType>
	class treeIterator
	{
		template<typename U, typename Compare, typename Alloc>
		friend class Avl;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef std::bidirectional_iterator_tag iterator_category;

			typedef T value_type;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef T& reference;
			typedef const T& const_reference;

			typedef std::ptrdiff_t difference_type;

		private:
			typedef NodeType<value_type>* node_pointer;

			typedef const T const_value_type;
			typedef treeIterator<const_value_type, NodeType> const_treeIterator;
			typedef NodeType<const_value_type>* const_treeIterator_node_pointer;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			treeIterator() : _ptr(0), _last(0), _isEnd(false)
			{
			}

			treeIterator(node_pointer ptr, node_pointer *last, bool isEnd) : _ptr(ptr), _last(last), _isEnd(isEnd)
			{
			}

			treeIterator(const treeIterator& src) : _ptr(src._ptr), _last(src._last), _isEnd(src._isEnd)
			{
			}

			treeIterator	operator=(const treeIterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				_last = rop._last;
				_isEnd = rop._isEnd;
				return *this;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Relational operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			friend bool	operator==(const treeIterator& lhs, const treeIterator& rhs)
			{
				return lhs._ptr == rhs._ptr && lhs._last == rhs._last && lhs._isEnd == rhs._isEnd;
			}

			friend bool	operator!=(const treeIterator& lhs, const treeIterator& rhs)
			{
				return !(lhs._ptr == rhs._ptr);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Relational operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			reference	operator*()
			{
				return _ptr->value;
			}

			const_reference	operator*() const
			{
				return _ptr->value;
			}

			pointer	operator->()
			{
				return &(_ptr->value);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Derefrence operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			treeIterator	&operator++()
			{
				//end or after end
				if (!_ptr)
				{
					_isEnd = false;
					return *this;
				}
				//inside the sequence
				_ptr = _ptr->getInOrderSuccessor();
				if (_ptr)
					return *this;
				//point at end now
				_isEnd = true;
				return *this;
			}

			treeIterator	operator++(int n)
			{
				treeIterator	ret(*this);

				(void)n;
				//end or after end
				if (!_ptr)
				{
					_isEnd = false;
					return ret;
				}
				//inside the sequence
				_ptr = _ptr->getInOrderSuccessor();
				if (_ptr)
					return ret;
				//point at end now
				_isEnd = true;
				return ret;
			}

			treeIterator	&operator--()
			{
				//at end : return last and restore the normal iterator state
				if (_isEnd)
				{
					_ptr = *_last;
					_isEnd = false;
				}
				//inside the sequence
				else if (_ptr)
					_ptr = _ptr->getInOrderPredeccessor();
				//outside of the sequence : do nothing
				return *this;
			}

			treeIterator	operator--(int n)
			{
				treeIterator	ret(*this);

				(void)n;
				//at end : return last and restore the normal iterator state
				if (_isEnd)
				{
					_ptr = *_last;
					_isEnd = false;
				}
				//inside the sequence
				else if (_ptr)
					_ptr = _ptr->getInOrderPredeccessor();
				//outside of the sequence : do nothing
				return ret;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Arithmetic operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Conversion operator
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			operator const_treeIterator() const
			{
				return const_treeIterator(reinterpret_cast<const_treeIterator_node_pointer>(_ptr), reinterpret_cast<const_treeIterator_node_pointer *>(_last), _isEnd);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Conversion operator
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Attributes
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			node_pointer	_ptr;
			node_pointer	*_last;
			bool			_isEnd;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Attributes End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};
}

#endif