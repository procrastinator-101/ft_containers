#ifndef AVL_HPP
# define AVL_HPP

#include <cstdlib>
#include <stack>
#include <iostream>

namespace ft
{
	template<typename T, typename Compare, typename Alloc>
	class Avl;

	template<typename T, typename Compare, typename Alloc>
	std::ostream &operator<<(std::ostream& ostr, const Avl<T, Compare, Alloc>& tree);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// External
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Trunk
	{
		Trunk		*prev;
		std::string	str;
	
		Trunk(Trunk *aprev, std::string astr)
		{
			prev = aprev;
			str = astr;
		}
	};
	void showTrunks(std::ostream& ostr, Trunk *p);
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// External
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename T, typename Compare, typename Alloc>
	class Avl
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Node class Defintion
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// private:
		private:
			class Node
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/// type definitions
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				public:
					typedef Compare value_compare;

					typedef T value_type;
					typedef T* pointer;
					typedef const T* const_pointer;
					typedef T& reference;
					typedef const T* const_reference;

					typedef Node* node_pointer;
					typedef const Node* const_node_pointer;
					typedef Node& node_reference;
					typedef const Node& const_node_reference;

					typedef size_t size_type;
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/// type definitions End
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Traits class Defintion
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				public:
					class Traits
					{
						public:
							node_pointer	left;
							node_pointer	right;
							node_pointer	parent;

							size_type		height;
						
						public:
							Traits() : left(0), right(0), parent(0), height(0)
							{
							}

							Traits(node_pointer left, node_pointer right, node_pointer parent, size_type height) : left(left), right(right), parent(parent), height(height)
							{
							}

							Traits(const Traits& src) : left(src.left), right(src.right), parent(src.parent), height(src.height)
							{
							}

							Traits	&operator=(const Traits& rop)
							{
								if (this == &rop)
									return *this;
								left = rop.left;
								right = rop.right;
								parent = rop.parent;
								height = rop.height;
								return *this;
							}
					};
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Traits class Defintion End
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				public:

					value_type	_value;
					Traits		_traits;


				public:

					Node();
					~Node();

					Node(value_type value);
					Node(value_type value, node_pointer left, node_pointer right, node_pointer parent);

					Node(const Node& src);
					node_reference	operator=(const Node& rhs);

					void    updateHeight();
					int     getBalanceFactor() const;

					node_pointer	getInOrderSuccessor() const;
					node_pointer	getInOrderPredeccessor() const;

					value_type		getValue() const;
					size_type		getHeight() const;

					node_pointer	getLeft() const;
					node_pointer	getRight() const;
					node_pointer	getParent() const;

					void	setValue(value_type value);
					void	setHeight(size_type height);

					void	setLeft(node_pointer left);
					void	setRight(node_pointer right);
					void	setParent(node_pointer parent);
			};
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Node class Defintion End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			typedef typename Node::value_compare value_compare;
			typedef typename Node::value_type value_type;

			typedef typename Node::pointer pointer;
			typedef typename Node::const_pointer const_pointer;
			typedef typename Node::reference reference;
			typedef typename Node::const_reference const_reference;

			typedef Alloc allocator_type;
			typedef typename allocator_type::template rebind<Node>::other node_allocator_type;
			typedef typename allocator_type::template rebind<typename Node::Traits>::other traits_allocator_type;

			typedef typename Node::size_type size_type;

		private:
			typedef typename Node::node_pointer node_pointer;
			typedef typename Node::const_node_pointer const_node_pointer;
			typedef typename Node::node_reference node_reference;
			typedef typename Node::const_node_reference const_node_reference;

			typedef typename Node::Traits Traits;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			Avl() : _root(0), _allocator(allocator_type()), _nodeAllocator(node_allocator_type())
			{
			}

			Avl(node_pointer root) : _root(root)
			{
			}

			Avl(const Avl& src) : _root(0), _allocator(src._allocator), _nodeAllocator(src._nodeAllocator)
			{
				node_pointer	tmp;
				node_pointer	node;

				for (node = src._root; node; node = node->getInOrderSuccessor())
				{
					tmp = _nodeAllocator.allocate(1);
					_traits_allocator.construct(&(tmp->_traits), node->_traits);
					try
					{
						_allocator.construct(&(tmp->_value), node->_value);
					}
					catch (...)
					{
						_traits_allocator.destroy(&(tmp->_traits));
						_nodeAllocator.deallocate(tmp, 1);
					}
					node->insert(_root, node);
				}
			}

			void	show() const
			{
				if (_root)
					std::cout << (*this) << std::endl;
			}

			friend std::ostream &operator<< <>(std::ostream& ostr, const Avl& tree);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			void	erase(const value_type& val);
			void	insert(const value_type& val);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Nodes manipulation functions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			void	_destroyNode(node_pointer node);
			node_pointer	_createNode(const value_type& val);

			//solates node from the rest of the tree (its parent does not recongnise him anymore 'poor child')
			void	_isolate(node_pointer node);
			//b steals the parent of a
			void	_replace(node_pointer a, node_pointer b);
			//child swaps position with its parent
			void	_swapRelatedNodes(node_pointer child, node_pointer parent);
			//a swaps position with b : a has no direct relationship with b
			void	_swapUnrelatedNodes(node_pointer a, node_pointer b);
			//a swaps position with b
			void	_swap(node_pointer a, node_pointer b);

			void	_balance(node_pointer node);
			void	_llRotate(node_pointer root);
			void	_rrRotate(node_pointer root);
			void	_lrRotate(node_pointer root);
			void	_rlRotate(node_pointer root);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Nodes manipulation functions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			node_pointer	_root;
			allocator_type	_allocator;
			node_allocator_type	_nodeAllocator;
			traits_allocator_type	_traits_allocator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// External
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		friend void	printTree(std::ostream& ostr, const_node_pointer root, Trunk *prev, bool isLeft)
		{
			if (root == nullptr) {
				return;
			}
		
			std::string prev_str = "    ";
			Trunk *trunk = new Trunk(prev, prev_str);
		
			printTree(ostr, root->getRight(), trunk, true);
		
			if (!prev) {
				trunk->str = "———";
			}
			else if (isLeft)
			{
				trunk->str = ".———";
				prev_str = "   |";
			}
			else {
				trunk->str = "`———";
				prev->str = prev_str;
			}
		
			showTrunks(ostr, trunk);
			// ostr << " " << root->getValue() << "(" << root->getHeight() << ")" << std::endl;
			// ostr << " (" << root->getValue() << " | " << (root->getParent() ? root->getParent()->getValue() : -1) << ")" << std::endl;
			ostr << " " << root->getValue() << std::endl;
			if (prev) {
				prev->str = prev_str;
			}
			trunk->str = "   |";
		
			printTree(ostr, root->getLeft(), trunk, false);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// External End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Node::Node() :  _value(), _traits()
	{
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Node::~Node()
	{
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Node::Node(value_type value, node_pointer left, node_pointer right, node_pointer parent) : _value(value), _traits(left, right, parent)
	{
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Node::Node(const Node& src) : _value(src._value), _traits(src._traits)
	{
	}

	template<typename T, typename Compare, typename Alloc>
	Avl<T, Compare, Alloc>::Node::Node(value_type value) : _value(value), _traits()
	{
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_reference	Avl<T, Compare, Alloc>::Node::operator=(const Node& rhs)
	{
		_value = rhs._value;
		_traits = rhs._traits;
		return *this;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
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

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::_balance(node_pointer node)
	{
		int balanceFactor;
		int subBalanceFactor;

		balanceFactor = node->getBalanceFactor();
		// std::cout << "balanceFactor : " << balanceFactor << std::endl;
		if (abs(balanceFactor) < 2)
			return ;
		if (balanceFactor < 0)
		{
			subBalanceFactor = node->_traits.right->getBalanceFactor();
			// std::cout << "RsubBalanceFactor : " << subBalanceFactor << std::endl;
			if (subBalanceFactor <= 0)
				_rrRotate(node);
			else
				_rlRotate(node);
		}
		else
		{
			subBalanceFactor = node->_traits.left->getBalanceFactor();
			// std::cout << "LsubBalanceFactor : " << subBalanceFactor << std::endl;
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
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Nodes manipulation functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Tree manipulation functions
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::insert(const value_type& val)
	{
		node_pointer	node;
		node_pointer	current;

		node = _createNode(val);
		if (!_root)
			_root = node;
		else
		{
			current = _root;
			while (1)
			{
				//if the node value is less than the current node' value : insert on the left
				if (Compare()(node->_value, current->_value))
				{
					if (current->_traits.left)
					{
						current = current->_traits.left;
						continue ;
					}
					else
					{
						current->_traits.left = node;
						node->_traits.parent = current;
						break ;
					}
				}
				else if (Compare()(current->_value, node->_value))
				{
					if (current->_traits.right)
					{
						current = current->_traits.right;
						continue ;
					}
					else
					{
						current->_traits.right = node;
						node->_traits.parent = current;
						break ;
					}
				}
				else
				{
					current->_value = node->_value;
					_destroyNode(node);
					break ;
				}
			}
			while (current)
			{
				current->updateHeight();
				_balance(current);
				current = current->_traits.parent;
			}
		}
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::erase(const value_type& val)
	{
		node_pointer	parent;
		node_pointer	current;
		node_pointer	candidate;

		current = _root;
		while (current)
		{
			//if val is less than the current node' value : erase on the left
			if (Compare()(val, current->_value))
			{
				if (current->_traits.left)
				{
					current = current->_traits.left;
					continue ;
				}
				break ;
			}
			else if (Compare()(current->_value, val))
			{
				if (current->_traits.right)
				{
					current = current->_traits.right;
					continue ;
				}
				break ;
			}
			else
			{
				//the to-delete node has a both childs
				if (current->_traits.left && current->_traits.right)
				{
					std::cout << "looking for candidate" << std::endl;
					candidate = current->getInOrderSuccessor();
					std::cout << "candidate found : " << candidate->_value << std::endl;
					_swap(current, candidate);
					candidate->updateHeight();
				}
				parent = current->_traits.parent;
				//the to-delete node has no children
				if (!current->_traits.left && !current->_traits.right)
					_isolate(current);
				//the to-delete node has a left child only
				else if (current->_traits.left)
					_replace(current, current->_traits.left);
				//the to-delete node has a right child only
				else if (current->_traits.right)
					_replace(current, current->_traits.right);
				while (parent)
				{
					parent->updateHeight();
					// std::cout << "height : " << parent->getHeight() << std::endl;
					// std::cout << "balanceFactor : " << parent->getBalanceFactor() << std::endl;
					_balance(parent);
					// std::cout << "balanceFactor End: " << parent->getBalanceFactor() << std::endl;
					parent = parent->_traits.parent;
				}
				_destroyNode(current);
				break ;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Tree manipulation functions End
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
	/// Node Functions
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::updateHeight()
	{
		size_type	leftHeight;
		size_type	rightHeight;

		if (_traits.left)
			leftHeight =_traits.left->_traits.height + 1;
		else
			leftHeight = 0;
		if (_traits.right)
			rightHeight =_traits.right->_traits.height + 1;
		else
			rightHeight = 0;
		_traits.height = std::max(leftHeight, rightHeight);
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getInOrderSuccessor() const
	{
		node_pointer	ret;

		//the smallest key that is larger than x

		ret = 0;
		//left most child of its right suNode
		if (_traits.right)
		{
			ret = _traits.right;
			while (ret->_traits.left)
				ret = ret->_traits.left;
		}
		//first parent with a key larger than that of the current node
		else
		{
			ret = _traits.parent;
			while (ret && ret->_value < _value)
				ret = ret->_traits.parent;
		}
		return ret;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getInOrderPredeccessor() const
	{
		node_pointer	ret;

		//the largest key that is smaller than x

		ret = 0;
		//right most child of its left suNode
		if (_traits.left)
		{
			ret = _traits.left;
			while (ret->_traits.right)
				ret = ret->_traits.right;
		}
		//first parent with a key samller than that of the current node
		else
		{
			ret = _traits.parent;
			while (ret && ret->_value > _value)
				ret = ret->_traits.parent;
		}
		return ret;
	}

	template<typename T, typename Compare, typename Alloc>
	int	Avl<T, Compare, Alloc>::Node::getBalanceFactor() const
	{
		size_type	leftHeight;
		size_type	rightHeight;

		if (_traits.left)
			leftHeight =_traits.left->_traits.height + 1;
		else
			leftHeight = 0;
		if (_traits.right)
			rightHeight =_traits.right->_traits.height + 1;
		else
			rightHeight = 0;
		return leftHeight - rightHeight;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Node Functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Node Getters
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::value_type	Avl<T, Compare, Alloc>::Node::getValue() const
	{
		return _value;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::size_type	Avl<T, Compare, Alloc>::Node::getHeight() const
	{
		return _traits.height;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getLeft() const
	{
		return _traits.left;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getRight() const
	{
		return _traits.right;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getParent() const
	{
		return _traits.parent;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Node Getters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Node Setters
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setValue(value_type value)
	{
		_value = value;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setHeight(size_type height)
	{
		_traits.height = height;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setLeft(node_pointer left)
	{
		_traits.left = left;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setRight(node_pointer right)
	{
		_traits.right = right;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setParent(node_pointer parent)
	{
		_traits.parent = parent;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Node Setters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Ostream operator << overload
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	std::ostream &operator<<(std::ostream& ostr, const Avl<T, Compare, Alloc>& tree)
	{
		ostr << "======================================================================================================================" << std::endl;
		printTree(ostr, tree._root, nullptr, false);
		ostr << "======================================================================================================================" << std::endl;
		return ostr;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Ostream operator << overload End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
}


#endif