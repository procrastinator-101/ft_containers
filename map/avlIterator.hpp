#ifndef AVLITERATOR_HPP
# define AVLITERATOR_HPP

#include <iterator>

namespace ft
{
	template<class Node>
	class avlIterator
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename Node::value_type value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename Node::pointer pointer;
			typedef typename Node::reference reference;
			typedef typename Node::const_pointer const_pointer;
			typedef typename Node::const_reference const_reference;

		private:
			typedef typename Node::node_pointer node_pointer;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		private:
			node_pointer	*_last;
			node_pointer	_ptr;

			bool			_isEnd;

		public:
			avlIterator() : _last(0), _ptr(0), _isEnd(false)
			{
			}

			avlIterator(node_pointer ptr, node_pointer *last, bool isEnd) : _last(last), _ptr(ptr), _isEnd(isEnd)
			{
			}

			avlIterator(const avlIterator& src) : _last(src._last), _ptr(src._ptr), _isEnd(src._isEnd)
			{
			}

			avlIterator	operator=(const avlIterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				_last = rop._last;
				_isEnd = rop._isEnd;
				return *this;
			}

			friend bool	operator==(const avlIterator& lhs, const avlIterator& rhs)
			{
				return lhs._ptr == rhs._ptr && lhs._last == rhs._last;
			}

			friend bool	operator!=(const avlIterator& lhs, const avlIterator& rhs)
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

			avlIterator	&operator++()
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

			avlIterator	operator++(int n)
			{
				avlIterator	ret(*this);

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

			avlIterator	&operator--()
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

			avlIterator	operator--(int n)
			{
				avlIterator	ret(*this);

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

			operator const_treeIterator<Node>() const
			{
				return const_treeIterator<Node>(_ptr, _last, _isEnd);
			}
	};
}

#endif