#ifndef CONST_TREEITERATOR_HPP
# define CONST_TREEITERATOR_HPP

#include <iterator>

namespace ft
{
	template<class NodeType>
	class const_treeIterator
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
			const_treeIterator() : _last(0), _ptr(0), _isEnd(false)
			{
			}

			const_treeIterator(node_pointer ptr, node_pointer last, bool isEnd) : _last(last), _ptr(ptr), _isEnd(isEnd)
			{
			}

			const_treeIterator(const const_treeIterator& src) : _last(src._last), _ptr(src._ptr), _isEnd(src._isEnd)
			{
			}

			const_treeIterator	operator=(const const_treeIterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				_last = rop._last;
				_isEnd = rop._isEnd;
				return *this;
			}

			friend bool	operator==(const const_treeIterator& lhs, const const_treeIterator& rhs)
			{
				return lhs._ptr == rhs._ptr && lhs._last == rhs._last;
			}

			friend bool	operator!=(const const_treeIterator& lhs, const const_treeIterator& rhs)
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

			const_treeIterator	&operator++()
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

			const_treeIterator	operator++(int n)
			{
				const_treeIterator	ret(*this);

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

			const_treeIterator	&operator--()
			{
				//at end : return last and restore the normal iterator state
				if (_isEnd)
				{
					if (_last)
						_ptr = *_last;
					else
						_ptr = 0;
					_isEnd = false;
				}
				//inside the sequence
				else if (_ptr)
					_ptr = _ptr->getInOrderPredeccessor();
				//outside of the sequence : do nothing
				return *this;
			}

			const_treeIterator	operator--(int n)
			{
				const_treeIterator	ret(*this);

				(void)n;
				//at end : return last and restore the normal iterator state
				if (_isEnd)
				{
					if (_last)
						_ptr = *_last;
					else
						_ptr = 0;
					_isEnd = false;
				}
				//inside the sequence
				else if (_ptr)
					_ptr = _ptr->getInOrderPredeccessor();
				//outside of the sequence : do nothing
				return ret;
			}
	};
}

#endif