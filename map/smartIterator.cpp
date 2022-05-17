#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

#include <iterator>

namespace ft
{
	template<typename T, template<typename> class Compare, template<typename, typename> class NodeType>
	class treeIterator
	{
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

			typedef Compare<value_type> value_compare;
			typedef NodeType<value_type, value_compare> Node;
			
			typedef std::ptrdiff_t difference_type;

		private:
			typedef Node* node_pointer;
			typedef const T const_value_type;
			typedef Compare<const_value_type> const_value_compare;
			typedef treeIterator<const_value_type, Compare, NodeType > const_iterator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		private:
			bool			_isEnd;
			node_pointer	_ptr;
			node_pointer	_last;

		public:
			treeIterator() : _ptr(0), _last(0), _isEnd(false)
			{
			}

			treeIterator(node_pointer ptr) : _ptr(ptr), _last(0), _isEnd(false)
			{
			}

			treeIterator(node_pointer ptr, node_pointer last) : _ptr(ptr), _last(last), _isEnd(true)
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

			friend bool	operator==(const treeIterator& lhs, const treeIterator& rhs)
			{
				return lhs._ptr == rhs._ptr && lhs._last == rhs._last && lhs._isEnd == rhs._isEnd;
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
				node_pointer	prev;

				//end or after end
				if (!_ptr)
				{
					_isEnd = false;
					_last = 0;
					return *this;
				}
				//inside the sequence
				prev = _ptr;
				_ptr = _ptr->getInOrderSuccessor();
				if (_ptr)
					return *this;
				//point at end now
				_isEnd = true;
				_last = prev;
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
					_last = 0;
					return ret;
				}
				//inside the sequence
				_ptr = _ptr->getInOrderSuccessor();
				if (_ptr)
					return ret;
				//point at end now
				_isEnd = true;
				_last = ret._ptr;
				return ret;
			}

			treeIterator	&operator--()
			{
				//at end : return last and restore the normal iterator state
				if (_isEnd)
				{
					_ptr = _last;
					_isEnd = false;
					_last = 0;
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
					_last = 0;
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