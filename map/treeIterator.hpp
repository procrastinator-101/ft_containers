#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

#include <iterator>

namespace ft
{
	template<typename T, typename Compare, typename Alloc>
	class Avl;

	template<typename Tree>
	class treeIterator
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename Tree::Node::value_type value_type;
			typedef std::ptrdiff_t difference_type;
			typedef typename Tree::Node::pointer pointer;
			typedef typename Tree::Node::reference reference;
			typedef typename Tree::Node::const_pointer const_pointer;
			typedef typename Tree::Node::const_reference const_reference;

			typedef Tree* tree_pointer;

		private:
			typedef Tree* node_pointer;
			typedef typename Tree::Node::value_compare value_compare;
			typedef typename Tree::Node::allocator_type allocator_type;
			typedef typename Avl<const value_type, value_compare, allocator_type>::iterator const_iterator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		private:
			tree_pointer	_tree;
			node_pointer	_ptr;

		public:
			treeIterator() : _tree(0), _ptr(0)
			{
			}

			treeIterator(node_pointer ptr, tree_pointer tree) : _tree(tree), _ptr(ptr)
			{
			}

			treeIterator(const treeIterator& src) : _tree(src._tree), _ptr(src._ptr)
			{
			}

			treeIterator	operator=(const treeIterator& rop)
			{
				if (this == &rop)
					return *this;
				_ptr = rop._ptr;
				_tree = rop._tree;
				return *this;
			}

			friend bool	operator==(const treeIterator& lhs, const treeIterator& rhs)
			{
				return lhs._ptr == rhs._ptr && lhs._tree == rhs._tree;
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