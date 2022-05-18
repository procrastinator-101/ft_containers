#ifndef pconst_TREEITERATOR_HPP
# define pconst_TREEITERATOR_HPP

#include <iterator>

namespace ft
{
	template<typename T, template<typename> class NodeType>
	class const_treeIterator
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

			typedef NodeType<value_type> Node;
			
			typedef std::ptrdiff_t difference_type;

		// private:
			typedef Node* node_pointer;
			typedef const T const_value_type;
			typedef const_treeIterator<const_value_type, NodeType> const_const_treeIterator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		private:
			node_pointer	_ptr;
			node_pointer	*_last;
			bool			_isEnd;

		public:
			const_treeIterator() : _ptr(0), _last(0), _isEnd(false)
			{
			}

			const_treeIterator(node_pointer ptr) : _ptr(ptr), _last(0), _isEnd(false)
			{
			}

			const_treeIterator(node_pointer ptr, node_pointer last, bool isEnd) : _ptr(ptr), _last(last), _isEnd(isEnd)
			{
			}

			const_treeIterator(const const_treeIterator& src) : _ptr(src._ptr), _last(src._last), _isEnd(src._isEnd)
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
				return lhs._ptr == rhs._ptr && lhs._last == rhs._last && lhs._isEnd == rhs._isEnd;
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
				_last = &prev;
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
					_last = 0;
					return ret;
				}
				//inside the sequence
				_ptr = _ptr->getInOrderSuccessor();
				if (_ptr)
					return ret;
				//point at end now
				_isEnd = true;
				_last = &ret._ptr;
				return ret;
			}

			const_treeIterator	&operator--()
			{
				//at end : return last and restore the normal iterator state
				if (_isEnd)
				{
					_ptr = *_last;
					_isEnd = false;
					_last = 0;
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
					_ptr = *_last;
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