#ifndef AVL_HPP
# define AVL_HPP

#include "../utility/pair.hpp"
#include "../utility/make_pair.hpp"

#include "node.hpp"

#include "treeIterator.hpp"
#include "../iterator/reverse_iterator.hpp"


namespace ft
{
	template<typename T, typename Compare, typename Alloc>
	class Avl
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			typedef ft::Node<T> Node;
			typedef typename Node::Traits Traits;
			typedef typename Node::node_pointer node_pointer;
			typedef typename Node::const_node_pointer const_node_pointer;
			typedef typename Node::node_reference node_reference;
			typedef typename Node::const_node_reference const_node_reference;

		public:
			typedef Alloc allocator_type;

		private:
			typedef typename allocator_type::template rebind<Node>::other node_allocator_type;
			typedef typename allocator_type::template rebind<Traits>::other traits_allocator_type;

		public:
			typedef Compare value_compare;
			typedef typename Node::value_type value_type;

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
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:

			Avl();
			~Avl();

			Avl(const value_compare& compare = value_compare(), const allocator_type& alloc = allocator_type());
			Avl(const Avl& src);

			Avl	&operator=(const Avl& rop);
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
			void		clear();
			void		swap(Avl& x);
			size_type	erase(const value_type& val);
			pair<iterator,bool>	insert(const value_type& val);//might throw : strong guarantee
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Operations
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			iterator	find(const value_type& val);
			iterator	lower_bound(const value_type& val);
			iterator	upper_bound(const value_type& val);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Operations End
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
			void	_destroyNode(node_pointer node);//might throw 
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


			void	_clone(const Avl& src);//might throw : strong guarantee
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
			traits_allocator_type	traits_allocator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Avl() : _count(0), _root(0), _last(0), _begin(0), _allocator(), _nodeAllocator(), traits_allocator()
	{
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Avl(const Avl& src) : _count(0), _root(0), _last(0), _begin(0), _allocator(src._allocator), _nodeAllocator(src._nodeAllocator), traits_allocator(src.traits_allocator)
	{
		_clone(src);
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::~Avl()
	{
		clear();
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>	&Avl<T, Compare, Alloc>::operator=(const Avl& rop)
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
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::iterator	Avl<T, Compare, Alloc>::end()
	{
		return iterator(0, &_last, true);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::iterator	Avl<T, Compare, Alloc>::begin()
	{
		return iterator(_begin, &_last, false);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::reverse_iterator	Avl<T, Compare, Alloc>::rend()
	{
		return reverse_iterator(begin());
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::reverse_iterator	Avl<T, Compare, Alloc>::rbegin()
	{
		return reverse_iterator(end());
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_iterator	Avl<T, Compare, Alloc>::end() const
	{
		return const_iterator(0, &_last, true);
	}
	
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_iterator	Avl<T, Compare, Alloc>::begin() const
	{
		return const_iterator(_begin, &_last, false);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_reverse_iterator	Avl<T, Compare, Alloc>::rend() const
	{
		return const_reverse_iterator(begin());
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::const_reverse_iterator	Avl<T, Compare, Alloc>::rbegin() const
	{
		return const_reverse_iterator(end());
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
				if (Compare()(val, current->value))
				{
					if (current->traits.left)
						current = current->traits.left;
					else
					{
						node = _putInPosition(current, val, true);
						break ;
					}
				}
				//if val is greater than the current node' value : insert on the right
				else if (Compare()(current->value, val))
				{
					if (current->traits.right)
						current = current->traits.right;
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
			if (Compare()(val, current->value))
				current = current->traits.left;
			//if val is grater than the current node' value : erase on the right
			else if (Compare()(current->value, val))
				current = current->traits.right;
			//if val is equal to the current node' value : erase the current node
			else
			{
				_delete(current);
				ret = 1;
				break ;
			}
		}
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

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::swap(Avl& x)
	{
		std::swap(_count, x._count);
		std::swap(_root, x._root);
		std::swap(_last, x._last);
		std::swap(_begin, x._begin);
		std::swap(_allocator, x._allocator);
		std::swap(_nodeAllocator, x._nodeAllocator);
		std::swap(traits_allocator, x.traits_allocator);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Modifiers End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Operations
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::iterator	Avl<T, Compare, Alloc>::find(const value_type& val)
	{
		node_pointer	node;

		node = _root;
		while (node)
		{
			if (value_compare(node->value, val))
				node = node->traits.right;
			else if (value_compare(val, node->value))
				node = node->traits.left;
			else
				return iterator(node, &_last, false);
		}
		return end();
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::iterator	Avl<T, Compare, Alloc>::lower_bound(const value_type& val)
	{
		node_pointer	ret;
		node_pointer	node;

		ret = 0;
		node = _root;
		while (node)
		{
			if (value_compare(node->value, val))
				node = node->traits.right;
			else if (value_compare(val, node->value))
			{
				ret = node;
				node = node->traits.left;
			}
			else
				return iterator(node, &_last, false);
		}
		if (ret)
			return iterator(ret, &_last, false);
		return end();
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::iterator	Avl<T, Compare, Alloc>::upper_bound(const value_type& val)
	{
		node_pointer	ret;
		node_pointer	node;

		ret = 0;
		node = _root;
		while (node)
		{
			if (value_compare(node->value, val))
			{
				ret = node;
				node = node->traits.right;
			}
			else if (value_compare(val, node->value))
				node = node->traits.left;
			else
			{
				ret = node->getInOrderSuccessor();
				break ;
			}
		}
		if (ret)
			return iterator(ret, &_last, false);
		return end();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Operations End
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
		try
		{
			traits_allocator.construct(&(node->traits), Traits());
		}
		catch (...)
		{
			_nodeAllocator.deallocate(node, 1);
		}
		try
		{
			_allocator.construct(&(node->value), val);
		}
		catch (...)
		{
			traits_allocator.destroy(&(node->traits));
			_nodeAllocator.deallocate(node, 1);
		}
		return node;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_destroyNode(node_pointer node)
	{
		_allocator.destroy(&(node->value));
		traits_allocator.destroy(&(node->traits));
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
			subBalanceFactor = node->traits.right->getBalanceFactor();
			if (subBalanceFactor <= 0)
				_rrRotate(node);
			else
				_rlRotate(node);
		}
		else
		{
			subBalanceFactor = node->traits.left->getBalanceFactor();
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
		if (node->traits.parent)
		{
			if (node->traits.parent->traits.left == node)
				node->traits.parent->traits.left = 0;
			else
				node->traits.parent->traits.right = 0;
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
		b->traits.parent = a->traits.parent;
		if (a->traits.parent)
		{
			if (a->traits.parent->traits.left == a)
				a->traits.parent->traits.left = b;
			else
				a->traits.parent->traits.right = b;
		}
		else
			_root = b;
	}

	//child swaps position with its parent
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_swapRelatedNodes(node_pointer child, node_pointer parent)
	{
		Traits	tmp;

		tmp = parent->traits;
		//the child abdicates its parent parents
		_replace(parent, child);
		//parent takes over the child's children
		parent->traits.left = child->traits.left;
		if (parent->traits.left)
			parent->traits.left->traits.parent = parent;
		parent->traits.right = child->traits.right;
		if (parent->traits.right)
			parent->traits.right->traits.parent = parent;
		//child takes over the parent's children
			//child was the left child of parent
		if (tmp.left == child)
		{
			child->traits.left = parent;
			child->traits.right = tmp.right;
			if (child->traits.right)
				child->traits.right->traits.parent = child;
		}
			//child was the right child of parent
		else
		{
			child->traits.right = parent;
			child->traits.left = tmp.left;
			if (child->traits.left)
				child->traits.left->traits.parent = child;
		}
		parent->traits.parent = child;
	}

	//a swaps position with b : a has no direct relationship with b
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_swapUnrelatedNodes(node_pointer a, node_pointer b)
	{
		Traits	tmp;

		tmp = b->traits;
		//b adicates a's parent
		_replace(a, b);
		//children swap
			//give the children of 'a' to the b
		b->traits.left = a->traits.left;
		b->traits.right = a->traits.right;
			//make the new children of b recognise b as their parent
		if (b->traits.left)
			b->traits.left->traits.parent = b;
		if (b->traits.right)
			b->traits.right->traits.parent = b;
			//get the children of b from the custodian and give them to 'a'
		a->traits.left = tmp.left;
		a->traits.right = tmp.right;
			//make the new children of 'a' recognise b as their parent
		if (a->traits.left)
			a->traits.left->traits.parent = a;
		if (a->traits.right)
			a->traits.right->traits.parent = a;
		//the exparent of b adopts a
		a->traits.parent = tmp.parent;
		if (tmp.parent)
		{
			if (tmp.parent->traits.left == b)
				a->traits.parent->traits.left = a;
			else
				a->traits.parent->traits.right = a;
		}
		else
			_root = a;
	}

	//a swaps position with b
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_swap(node_pointer a, node_pointer b)
	{
		if (a->traits.parent == b)
			_swapRelatedNodes(a, b);
		else if (b->traits.parent == a)
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
		if (node->traits.left && node->traits.right)
		{
			candidate = node->getInOrderSuccessor();
			_swap(node, candidate);
			candidate->updateHeight();
		}
		parent = node->traits.parent;
		//the to-delete node has no children
		if (!node->traits.left && !node->traits.right)
			_isolate(node);
		//the to-delete node has a left child only
		else if (node->traits.left)
			_replace(node, node->traits.left);
		//the to-delete node has a right child only
		else if (node->traits.right)
			_replace(node, node->traits.right);
		//update the height of the upper subtree and balance
		_retroBalance(parent);
		_destroyNode(node);
		--_count;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_destorySubtree(node_pointer root)
	{
		if (!root)
			return;
		_destorySubtree(root->traits.left);
		_destorySubtree(root->traits.right);
		_destroyNode(root);
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_retroBalance(node_pointer node)
	{
		while (node)
		{
			node->updateHeight();
			_balance(node);
			node = node->traits.parent;
		}
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_clone(const Avl& src)
	{
		node_pointer	node;

		try
		{
			for (node = src._root; node; node = node->getInOrderSuccessor())
				insert(node->value);
		}
		catch (...)
		{
			clear();
		}
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

		newRoot = root->traits.left;

		//replace the current root with the newRoot
		_replace(root, newRoot);
		
		//make the current root the right child of the newRoot
			//let the right child of the newRoot (current root) embrace its left child
		root->traits.left = newRoot->traits.right;
		if (root->traits.left)
			root->traits.left->traits.parent = root;
			//let the newroot welcome its right child
		root->traits.parent = newRoot;
		newRoot->traits.right = root;

		//update the height of newRoot and its childs
		newRoot->traits.left->updateHeight();
		newRoot->traits.right->updateHeight();
		newRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_rrRotate(node_pointer root)
	{
		node_pointer	newRoot;

		newRoot = root->traits.right;

		//replace the current root with the newRoot
		_replace(root, newRoot);
		
		//make the current root the left child of the newRoot
			//let the left child of the newRoot embrace its right child
		root->traits.right = newRoot->traits.left;
		if (root->traits.right)
			root->traits.right->traits.parent = root;
			//let the newroot welcome its left child
		root->traits.parent = newRoot;
		newRoot->traits.left = root;
		
		//update the height of newRoot and its childs
		newRoot->traits.left->updateHeight();
		newRoot->traits.right->updateHeight();
		newRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_lrRotate(node_pointer root)
	{
		node_pointer	newRoot;

		newRoot = root->traits.left->traits.right;

		//replace the current node with the newRoot
		_replace(root, newRoot);
		
		//adjsut the left child of the newRoot
			//let the left child of the newroot embrace its new right child
		root->traits.left->traits.right = newRoot->traits.left;
		if (newRoot->traits.left)
			newRoot->traits.left->traits.parent = root->traits.left;
			//let the newroot welcome its left child
		newRoot->traits.left = root->traits.left;
		root->traits.left->traits.parent = newRoot;

		//adjust the right child of the newRoot
			//let the right child of the newroot embrace its new left child
		root->traits.left = newRoot->traits.right;
		if (root->traits.left)
			root->traits.left->traits.parent = root;
			//let the newroot welcome its right child
		newRoot->traits.right = root;
		root->traits.parent = newRoot;

		//update the height of newRoot and its childs
		newRoot->traits.left->updateHeight();
		newRoot->traits.right->updateHeight();
		newRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_rlRotate(node_pointer root)
	{
		node_pointer	newRoot;

		newRoot = root->traits.right->traits.left;

		//replace the current node with the newRoot
		_replace(root, newRoot);
		
		//adjsut the right child of the newRoot
			//let the right child of the newroot embrace its new left child
		root->traits.right->traits.left = newRoot->traits.right;
		if (newRoot->traits.right)
			newRoot->traits.right->traits.parent = root->traits.right;
			//let the newroot welcome its right child
		newRoot->traits.right = root->traits.right;
		root->traits.right->traits.parent = newRoot;

		//adjsut the left child of the newRoot
			//let the left child of the newroot embrace its new right child
		root->traits.right = newRoot->traits.left;
		if (root->traits.right)
			root->traits.right->traits.parent = root;
			//let the newroot welcome its left child
		newRoot->traits.left = root;
		root->traits.parent = newRoot;

		//update the height of newRoot and its childs
		newRoot->traits.left->updateHeight();
		newRoot->traits.right->updateHeight();
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
			parent->traits.left = node;
			node->traits.parent = parent;
		}
		else
		{
			parent->traits.right = node;
			node->traits.parent = parent;
		}
		_updateBoundsInsert(parent);
		++_count;
		return node;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::node_pointer	Avl<T, Compare, Alloc>::_putInPosition(node_pointer node, const value_type& val)
	{
		node->value = val;
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
		++_count;
		return node;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// auxiliaries End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif