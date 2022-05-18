#ifndef AVL_HPP
# define AVL_HPP

#include <cstdlib>
#include <stack>
#include <iostream>
#include <type_traits>

#include "../utility/pair.hpp"
#include "../utility/make_pair.hpp"

#include "node.hpp"
#include "../iterator/reverse_iterator.hpp"


#include "../utility/pair.hpp"
#include "../utility/make_pair.hpp"

#include "smartIterator.hpp"


namespace ft
{
	template<typename T, typename Compare, typename Alloc>
	class Avl
	{
		template<typename Tree>
		friend class iterator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			typedef ft::Node<T> Node;
			typedef typename Node::node_pointer node_pointer;
			typedef typename Node::const_node_pointer const_node_pointer;
			typedef typename Node::node_reference node_reference;
			typedef typename Node::const_node_reference const_node_reference;

			typedef typename Node::Traits Traits;

			typedef Alloc allocator_type;
			typedef typename allocator_type::template rebind<Node>::other node_allocator_type;//!!!!!!!!!!
			typedef typename allocator_type::template rebind<typename Node::Traits>::other traits_allocator_type;//!!!!!!!!

		public:
			typedef typename Node::value_type value_type;
			typedef typename Node::Compare value_compare;

			typedef typename Node::pointer pointer;
			typedef typename Node::const_pointer const_pointer;
			typedef typename Node::reference reference;
			typedef typename Node::const_reference const_reference;

			typedef typename Node::size_type size_type;

			typedef treeIterator<T, ft::Node> iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef treeIterator<const T, ft::Node> const_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		



		public:
		void	show() const
		{
			printTree(std::cout, _root, 0, 0);
		}

		node_pointer	getRoot() const
		{
			return _root;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:

			Avl();
			~Avl();

			Avl(const value_compare& compare = value_compare(), const allocator_type& alloc = allocator_type());
			Avl(node_pointer root);
			Avl(const Avl& src);

			Avl	&operator=(const Avl& rop)
			{
				if (this == &rop)
					return *this;
				clear();
				_clone(rop);
				return *this;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Iterators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			iterator	end();
			iterator	begin();

			reverse_iterator	rend();
			reverse_iterator	rbegin();

			const_iterator	end() const;
			const_iterator	begin() const;

			const_reverse_iterator	rend() const;
			const_reverse_iterator	rbegin() const;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Iterators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			void	clear();
			size_type	erase(const value_type& val);
			size_type	erase(const node_pointer node);
			pair<iterator,bool>	insert(const value_type& val);


			iterator	find(const value_type& val)
			{
				node_pointer	node;

				node = _root;
				while (node)
				{
					if (value_compare(node->_value, val))
						node = node->_traits.right;
					else if (value_compare(val, node->_value))
						node = node->_traits.left;
					else
						return iterator(node, &_last, false);
				}
				return end();
			}

			iterator	lower_bound(const value_type& val)
			{
				node_pointer	ret;
				node_pointer	node;

				ret = 0;
				node = _root;
				while (node)
				{
					if (value_compare(node->_value, val))
						node = node->_traits.right;
					else if (value_compare(val, node->_value))
					{
						ret = node;
						node = node->_traits.left;
					}
					else
						return iterator(node, &_last, false);
				}
				if (ret)
					return iterator(ret, &_last, false);
				return end();
			}

			iterator	upper_bound(const value_type& val)
			{
				node_pointer	ret;
				node_pointer	node;

				ret = 0;
				node = _root;
				while (node)
				{
					if (value_compare(node->_value, val))
					{
						ret = node;
						node = node->_traits.right;
					}
					else if (value_compare(val, node->_value))
						node = node->_traits.left;
					else
						return iterator(node->getInOrderSuccessor(), &_last, false);
				}
				if (ret)
					return iterator(ret, &_last, false);
				return end();
			}

			void	swap(Avl& x)
			{
				std::swap(_count, x._count);
				std::swap(_root, x._root);
				std::swap(_last, x._last);
				std::swap(_begin, x._begin);
				std::swap(_allocator, x._allocator);
				std::swap(_nodeAllocator, x._nodeAllocator);
				std::swap(_traits_allocator, x._traits_allocator);
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Getters
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			size_type	getCount() const;
			size_type	max_size() const;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Getters End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Nodes manipulation functions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			void	_destroyNode(node_pointer node);
			node_pointer	_createNode(const value_type& val);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Nodes manipulation functions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Internal modifiers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			void	_balance(node_pointer node);
			void	_isolate(node_pointer node);
			void	_replace(node_pointer a, node_pointer b);
			void	_swap(node_pointer a, node_pointer b);
			void	_swapUnrelatedNodes(node_pointer a, node_pointer b);
			void	_swapRelatedNodes(node_pointer child, node_pointer parent);

			void	_delete(node_pointer node);
			void	_retroBalance(node_pointer node);
			void	_destorySubtree(node_pointer root);


			void	_clone(const Avl& src);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Internal modifiers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Rotations
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			void	_llRotate(node_pointer root);
			void	_rrRotate(node_pointer root);
			void	_lrRotate(node_pointer root);
			void	_rlRotate(node_pointer root);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Rotations End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// auxiliaries
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			void	_updateBoundsInsert(node_pointer node);
			void	_updateBoundsDelete(node_pointer node);

			node_pointer	_putInPosition(const value_type& val);
			node_pointer	_putInPosition(node_pointer node, const value_type& val);
			node_pointer	_putInPosition(node_pointer parent, const value_type& val, bool isLeft);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// auxiliaries
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Allocator
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			allocator_type	get_allocator() const
			{
				return _allocator;
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Allocator End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			size_type		_count;
			node_pointer	_root;
			node_pointer	_last;
			node_pointer	_begin;
			allocator_type	_allocator;
			node_allocator_type	_nodeAllocator;
			traits_allocator_type	_traits_allocator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Avl() : _count(0), _root(0), _last(_root), _begin(_root), _allocator(allocator_type()), _nodeAllocator(node_allocator_type()), _traits_allocator(traits_allocator_type())
	{
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Avl(node_pointer root) : _count(0), _root(root), _last(_root), _begin(_root), _allocator(), _nodeAllocator(), _traits_allocator(traits_allocator_type())
	{
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Avl(const Avl& src) : _count(0), _root(0), _last(0), _begin(0), _allocator(src._allocator), _nodeAllocator(src._nodeAllocator), _traits_allocator(src._traits_allocator)
	{
		_clone(src);
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::~Avl()
	{
		clear();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Iterators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::iterator	Avl<T, Compare, Alloc>::begin()
	{
		// return iterator(_begin, _last, false);
		return iterator(_begin, &_last, false);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::iterator	Avl<T, Compare, Alloc>::end()
	{
		// return iterator(0, _last, true);
		return iterator(0, &_last, true);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::reverse_iterator	Avl<T, Compare, Alloc>::rbegin()
	{
		return reverse_iterator(end());
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::reverse_iterator	Avl<T, Compare, Alloc>::rend()
	{
		return reverse_iterator(begin());
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_iterator	Avl<T, Compare, Alloc>::end() const
	{
		// return const_iterator(0, _last, true);
		return const_iterator(0, &_last, true);
	}
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_iterator	Avl<T, Compare, Alloc>::begin() const
	{

	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_reverse_iterator	Avl<T, Compare, Alloc>::rend() const
	{

	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_reverse_iterator	Avl<T, Compare, Alloc>::rbegin() const
	{

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Iterators End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Modifiers
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	pair<typename Avl<T, Compare, Alloc>::iterator,bool>	Avl<T, Compare, Alloc>::insert(const value_type& val)
	{
		bool			isnew;
		node_pointer	node;
		node_pointer	current;

		isnew = true;
		if (!_root)
			node = _putInPosition(val);
		else
		{
			current = _root;
			while (1)
			{
				//if val is less than the current node' value : insert on the left
				if (Compare()(val, current->_value))
				{
					if (current->_traits.left)
						current = current->_traits.left;
					else
					{
						node = _putInPosition(current, val, true);
						break ;
					}
				}
				//if val is greater than the current node' value : insert on the right
				else if (Compare()(current->_value, val))
				{
					if (current->_traits.right)
						current = current->_traits.right;
					else
					{
						node = _putInPosition(current, val, false);
						break ;
					}
				}
				//if val is equal to the current node' value : insert in the current node
				else
				{
					node = _putInPosition(current, val);
					isnew = false;
					break ;
				}
			}
			_retroBalance(current);
		}
		_count++;
		return make_pair(iterator(node, &_last, false), isnew);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::size_type	Avl<T, Compare, Alloc>::erase(const value_type& val)
	{
		size_type		ret;
		node_pointer	current;

		ret = 0;
		current = _root;
		while (current)
		{
			//if val is less than the current node' value : erase on the left
			if (Compare()(val, current->_value))
				current = current->_traits.left;
			//if val is grater than the current node' value : erase on the right
			else if (Compare()(current->_value, val))
				current = current->_traits.right;
			//if val is equal to the current node' value : erase the current node
			else
			{
				_delete(current);
				ret = 1;
				break ;
			}
		}
		_count--;
		return ret;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::size_type	Avl<T, Compare, Alloc>::erase(const node_pointer node)
	{
		size_type		ret;
		node_pointer	current;

		ret = 0;
		current = _root;
		while (current)
		{
			//if node' val is less than the current node' value : erase on the left
			if (Compare()(node->_value, current->_value))
				current = current->_traits.left;
			//if node' val is grater than the current node' value : erase on the right
			else if (Compare()(current->_value, node->_value))
				current = current->_traits.right;
			//if node' val is equal to the current node' value : erase the current node
			else
			{
				_delete(current);
				ret = 1;
				break ;
			}
		}
		_count--;
		return ret;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::clear()
	{
		_destorySubtree(_root);
		_count = 0;
		_root = 0;
		_last = 0;
		_begin = 0;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Modifiers End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::size_type	Avl<T, Compare, Alloc>::getCount() const
	{
		return _count;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::size_type	Avl<T, Compare, Alloc>::max_size() const
	{
		return _nodeAllocator.max_size();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Nodes manipulation functions
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::node_pointer	Avl<T, Compare, Alloc>::_createNode(const value_type& val)
	{
		node_pointer	node;

		node = _nodeAllocator.allocate(1);
		_traits_allocator.construct(&(node->_traits), Traits());
		try
		{
			_allocator.construct(&(node->_value), val);
		}
		catch (...)
		{
			_traits_allocator.destroy(&(node->_traits));
			_nodeAllocator.deallocate(node, 1);
		}
		return node;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_destroyNode(node_pointer node)
	{
		_allocator.destroy(&(node->_value));
		_traits_allocator.destroy(&(node->_traits));
		_nodeAllocator.deallocate(node, 1);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Nodes manipulation functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Internal modifiers End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_balance(node_pointer node)
	{
		int balanceFactor;
		int subBalanceFactor;

		balanceFactor = node->getBalanceFactor();
		if (abs(balanceFactor) < 2)
			return ;
		if (balanceFactor < 0)
		{
			subBalanceFactor = node->_traits.right->getBalanceFactor();
			if (subBalanceFactor <= 0)
				_rrRotate(node);
			else
				_rlRotate(node);
		}
		else
		{
			subBalanceFactor = node->_traits.left->getBalanceFactor();
			if (subBalanceFactor < 0)
				_lrRotate(node);
			else
				_llRotate(node);
		}
	}

	//solates node from the rest of the tree (its parent does not recongnise him anymore 'poor child')
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_isolate(node_pointer node)
	{
		if (node->_traits.parent)
		{
			if (node->_traits.parent->_traits.left == node)
				node->_traits.parent->_traits.left = 0;
			else
				node->_traits.parent->_traits.right = 0;
		}
		else
			_root = 0;
	}

	//b steals the parent of a
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_replace(node_pointer a, node_pointer b)
	{
		if (a == b)
			return ;
		b->_traits.parent = a->_traits.parent;
		if (a->_traits.parent)
		{
			if (a->_traits.parent->_traits.left == a)
				a->_traits.parent->_traits.left = b;
			else
				a->_traits.parent->_traits.right = b;
		}
		else
			_root = b;
	}

	//child swaps position with its parent
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_swapRelatedNodes(node_pointer child, node_pointer parent)
	{
		Traits	tmp;

		tmp = parent->_traits;
		//the child abdicates its parent parents
		_replace(parent, child);
		//parent takes over the child's children
		parent->_traits.left = child->_traits.left;
		if (parent->_traits.left)
			parent->_traits.left->_traits.parent = parent;
		parent->_traits.right = child->_traits.right;
		if (parent->_traits.right)
			parent->_traits.right->_traits.parent = parent;
		//child takes over the parent's children
			//child was the left child of parent
		if (tmp.left == child)
		{
			child->_traits.left = parent;
			child->_traits.right = tmp.right;
			if (child->_traits.right)
				child->_traits.right->_traits.parent = child;
		}
			//child was the right child of parent
		else
		{
			child->_traits.right = parent;
			child->_traits.left = tmp.left;
			if (child->_traits.left)
				child->_traits.left->_traits.parent = child;
		}
		parent->_traits.parent = child;
	}

	//a swaps position with b : a has no direct relationship with b
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_swapUnrelatedNodes(node_pointer a, node_pointer b)
	{
		Traits	tmp;

		tmp = b->_traits;
		//b adicates a's parent
		_replace(a, b);
		//children swap
			//give the children of 'a' to the b
		b->_traits.left = a->_traits.left;
		b->_traits.right = a->_traits.right;
			//make the new children of b recognise b as their parent
		if (b->_traits.left)
			b->_traits.left->_traits.parent = b;
		if (b->_traits.right)
			b->_traits.right->_traits.parent = b;
			//get the children of b from the custodian and give them to 'a'
		a->_traits.left = tmp.left;
		a->_traits.right = tmp.right;
			//make the new children of 'a' recognise b as their parent
		if (a->_traits.left)
			a->_traits.left->_traits.parent = a;
		if (a->_traits.right)
			a->_traits.right->_traits.parent = a;
		//the exparent of b adopts a
		a->_traits.parent = tmp.parent;
		if (tmp.parent)
		{
			if (tmp.parent->_traits.left == b)
				a->_traits.parent->_traits.left = a;
			else
				a->_traits.parent->_traits.right = a;
		}
		else
			_root = a;
	}

	//a swaps position with b
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_swap(node_pointer a, node_pointer b)
	{
		if (a->_traits.parent == b)
			_swapRelatedNodes(a, b);
		else if (b->_traits.parent == a)
			_swapRelatedNodes(b, a);
		else
			_swapUnrelatedNodes(a, b);
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_delete(node_pointer node)
	{
		node_pointer	parent;
		node_pointer	candidate;

		_updateBoundsDelete(node);
		//the to-delete node has a both childs
		if (node->_traits.left && node->_traits.right)
		{
			candidate = node->getInOrderSuccessor();
			_swap(node, candidate);
			candidate->updateHeight();
		}
		parent = node->_traits.parent;
		//the to-delete node has no children
		if (!node->_traits.left && !node->_traits.right)
			_isolate(node);
		//the to-delete node has a left child only
		else if (node->_traits.left)
			_replace(node, node->_traits.left);
		//the to-delete node has a right child only
		else if (node->_traits.right)
			_replace(node, node->_traits.right);
		//update the height of the upper subtree and balance
		_retroBalance(parent);
		_destroyNode(node);
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_destorySubtree(node_pointer root)
	{
		if (!root)
			return;
		_destorySubtree(root->_traits.left);
		_destorySubtree(root->_traits.right);
		_destroyNode(root);
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_retroBalance(node_pointer node)
	{
		while (node)
		{
			node->updateHeight();
			_balance(node);
			node = node->_traits.parent;
		}
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_clone(const Avl& src)
	{
		node_pointer	node;

		for (node = src._root; node; node = node->getInOrderSuccessor())
			insert(node->_value);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Internal modifiers End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Rotations
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_llRotate(node_pointer root)
	{
		node_pointer	newRoot;

		newRoot = root->_traits.left;

		//replace the current root with the newRoot
		_replace(root, newRoot);
		
		//make the current root the right child of the newRoot
			//let the right child of the newRoot (current root) embrace its left child
		root->_traits.left = newRoot->_traits.right;
		if (root->_traits.left)
			root->_traits.left->_traits.parent = root;
			//let the newroot welcome its right child
		root->_traits.parent = newRoot;
		newRoot->_traits.right = root;

		//update the height of newRoot and its childs
		newRoot->_traits.left->updateHeight();
		newRoot->_traits.right->updateHeight();
		newRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_rrRotate(node_pointer root)
	{
		node_pointer	newRoot;

		newRoot = root->_traits.right;

		//replace the current root with the newRoot
		_replace(root, newRoot);
		
		//make the current root the left child of the newRoot
			//let the left child of the newRoot embrace its right child
		root->_traits.right = newRoot->_traits.left;
		if (root->_traits.right)
			root->_traits.right->_traits.parent = root;
			//let the newroot welcome its left child
		root->_traits.parent = newRoot;
		newRoot->_traits.left = root;
		
		//update the height of newRoot and its childs
		newRoot->_traits.left->updateHeight();
		newRoot->_traits.right->updateHeight();
		newRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_lrRotate(node_pointer root)
	{
		node_pointer	newRoot;

		newRoot = root->_traits.left->_traits.right;

		//replace the current node with the newRoot
		_replace(root, newRoot);
		
		//adjsut the left child of the newRoot
			//let the left child of the newroot embrace its new right child
		root->_traits.left->_traits.right = newRoot->_traits.left;
		if (newRoot->_traits.left)
			newRoot->_traits.left->_traits.parent = root->_traits.left;
			//let the newroot welcome its left child
		newRoot->_traits.left = root->_traits.left;
		root->_traits.left->_traits.parent = newRoot;

		//adjust the right child of the newRoot
			//let the right child of the newroot embrace its new left child
		root->_traits.left = newRoot->_traits.right;
		if (root->_traits.left)
			root->_traits.left->_traits.parent = root;
			//let the newroot welcome its right child
		newRoot->_traits.right = root;
		root->_traits.parent = newRoot;

		//update the height of newRoot and its childs
		newRoot->_traits.left->updateHeight();
		newRoot->_traits.right->updateHeight();
		newRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_rlRotate(node_pointer root)
	{
		node_pointer	newRoot;

		newRoot = root->_traits.right->_traits.left;

		//replace the current node with the newRoot
		_replace(root, newRoot);
		
		//adjsut the right child of the newRoot
			//let the right child of the newroot embrace its new left child
		root->_traits.right->_traits.left = newRoot->_traits.right;
		if (newRoot->_traits.right)
			newRoot->_traits.right->_traits.parent = root->_traits.right;
			//let the newroot welcome its right child
		newRoot->_traits.right = root->_traits.right;
		root->_traits.right->_traits.parent = newRoot;

		//adjsut the left child of the newRoot
			//let the left child of the newroot embrace its new right child
		root->_traits.right = newRoot->_traits.left;
		if (root->_traits.right)
			root->_traits.right->_traits.parent = root;
			//let the newroot welcome its left child
		newRoot->_traits.left = root;
		root->_traits.parent = newRoot;

		//update the height of newRoot and its childs
		newRoot->_traits.left->updateHeight();
		newRoot->_traits.right->updateHeight();
		newRoot->updateHeight();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Rotations End
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// auxiliaries
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_updateBoundsInsert(node_pointer node)
	{
		node_pointer	tmp;

		if (node == _begin)
		{
			tmp = node->getInOrderPredeccessor();
			if (tmp)
				_begin = tmp;
		}
		if (node == _last)
		{
			tmp = node->getInOrderSuccessor();
			if (tmp)
				_last = tmp;
		}
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_updateBoundsDelete(node_pointer node)
	{
		if (node == _begin)
			_begin = node->getInOrderSuccessor();
		if (node == _last)
			_last = node->getInOrderPredeccessor();
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::node_pointer	Avl<T, Compare, Alloc>::_putInPosition(node_pointer parent, const value_type& val, bool isLeft)
	{
		node_pointer	node;

		node = _createNode(val);
		if (isLeft)
		{
			parent->_traits.left = node;
			node->_traits.parent = parent;
		}
		else
		{
			parent->_traits.right = node;
			node->_traits.parent = parent;
		}
		_updateBoundsInsert(parent);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::node_pointer	Avl<T, Compare, Alloc>::_putInPosition(node_pointer node, const value_type& val)
	{
		node->_value = val;
		return node;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::node_pointer	Avl<T, Compare, Alloc>::_putInPosition(const value_type& val)
	{
		node_pointer	node;

		node = _createNode(val);
		_root = node;
		_last = node;
		_begin = node;
		return node;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// auxiliaries End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif