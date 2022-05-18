#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

#include <iterator>

#include "const_treeIterator.hpp"

namespace ft
{
	template<class NodeType>
	class treeIterator
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename NodeType::value_type value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename NodeType::pointer pointer;
			typedef typename NodeType::reference reference;
			typedef typename NodeType::const_pointer const_pointer;
			typedef typename NodeType::const_reference const_reference;

		private:
			typedef typename NodeType::node_pointer node_pointer;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		private:
			node_pointer	_last;
			node_pointer	_ptr;

			bool			_isEnd;

		public:
			treeIterator() : _last(0), _ptr(0), _isEnd(false)
			{
			}

			treeIterator(node_pointer ptr, node_pointer last, bool isEnd) : _last(last), _ptr(ptr), _isEnd(isEnd)
			{
			}

			treeIterator(const treeIterator& src) : _last(src._last), _ptr(src._ptr), _isEnd(src._isEnd)
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

			friend bool	operator==(const treeIterator& lhs, const treeIterator& rhs)
			{
				return lhs._ptr == rhs._ptr && lhs._last == rhs._last;
			}

			friend bool	operator!=(const treeIterator& lhs, const treeIterator& rhs)
			{
				return !(lhs._ptr == rhs._ptr);
			}

			reference	operator*()
			{
				return _ptr->_value;
			}

			const_reference	operator*() const
			{
				return _ptr->_value;
			}

			pointer	operator->()
			{
				return &(_ptr->_value);
			}

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
					_ptr = _last;
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
					_ptr = _last;
					_isEnd = false;
				}
				//inside the sequence
				else if (_ptr)
					_ptr = _ptr->getInOrderPredeccessor();
				//outside of the sequence : do nothing
				return ret;
			}

			operator const_treeIterator<NodeType>() const
			{
				return const_treeIterator<NodeType>(_ptr, _last, _isEnd);
			}
	};
}

#endif