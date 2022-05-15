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


	template<typename T, typename Compare, typename Alloc>
	class Avl
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Node class Defintion
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// private:
		public:
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


					void	isolate(node_pointer &root);
					void	swap(node_pointer &root, node_pointer node);
					void	replace(node_pointer &root, node_pointer node);

					void    balance(node_pointer &root);

					void    llRotate(node_pointer &root);
					void    lrRotate(node_pointer &root);
					void    rlRotate(node_pointer &root);
					void    rrRotate(node_pointer &root);

					void    updateHeight();

					int     getBalanceFactor() const;


				public:

					Node();
					~Node();

					Node(value_type value);
					Node(value_type value, node_pointer left, node_pointer right, node_pointer parent);

					Node(const Node& src);
					node_reference	operator=(const Node& rhs);

					void	erase(node_pointer &root, value_type value);
					void	insert(node_pointer &root, node_pointer node);

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
			node_pointer	createNode(const value_type& val)
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

			void	destroyNode(node_pointer node)
			{
				_allocator.destroy(&(node->_value));
				_traits_allocator.destroy(&(node->_traits));
				_nodeAllocator.deallocate(node, 1);
			}

			void	insert(const value_type& val)
			{
				node_pointer	node;
				node_pointer	current;

				node = createNode(val);
				if (!_root)
					_root = node;
				else
				{
					current = _root;
					while (1)
					{
						//if the node value is less than the current node' value : insert on the left
						if (Compare(node->_value, current->_value))
						{
							if (current->_traits.left)
							{
								current = current->_traits.left;
								continue ;
							}
							else
							{
								current->_traits.left = node;
								node._parent = current;
								break ;
							}
						}
						else if (Compare(current->_value, node->_value))
						{
							if (current->_traits.right)
							{
								current = current->_traits.right;
								continue ;
							}
							else
							{
								current->_traits.right = node;
								node._parent = current;
								break ;
							}
						}
						else
						{
							current->_value = node->_value;
							destroyNode(node);
						}
					}
					while (current)
					{
						current->updateHeight();
						current->balance(current);
						current = current->_traits.parent;
					}
				}
			}

			void	erase(value_type value)
			{
				node_pointer	parent;
				node_pointer	current;
				node_pointer	candidate;

				current = _root;
				while (1)
				{
					//if the value is less than the current node' value : erase on the left
					if (Compare(value, current->_value))
					{
						if (current->_traits.left)
						{
							current = current->_traits.left;
							continue ;
						}
						break ;
					}
					else if (Compare(current->_value, value))
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
							swap(current, candidate);
							candidate->updateHeight();
						}
						parent = current->_traits.parent;
						//the to-delete node has no children
						if (!current->_traits.left && !current->_traits.right)
							isolate(current);
						//the to-delete node has a left child only
						else if (current->_traits.left)
							replace(current, current->_traits.left);
						//the to-delete node has a right child only
						else if (current->_traits.right)
							replace(current, current->_traits.right);
						while (parent)
						{
							parent->updateHeight();
							parent->balance(current);
							parent = parent->_traits.parent;
						}
						destroyNode(current);
						break ;
					}
				}
			}

			void	balance(node_pointer node)
			{
				int balanceFactor;
				int subBalanceFactor;

				balanceFactor = node->getBalanceFactor();
				if (abs(balanceFactor) < 2)
					return ;
				if (balanceFactor < 0)
				{
					subBalanceFactor = node->_right->getBalanceFactor();
					if (subBalanceFactor < 0)
						node->rrRotate();
					else if (subBalanceFactor > 0)
						node->rlRotate();
				}
				else
				{
					subBalanceFactor = node->_left->getBalanceFactor();
					if (subBalanceFactor < 0)
						node->lrRotate();
					else if (subBalanceFactor > 0)
						node->llRotate();
				}
			}

			//solates node from the rest of the tree (its parent does not recongnise him anymore 'poor child')
			void	isolate(node_pointer node)
			{
				if (node->_traits.parent)
				{
					if (node->_traits.parent->_traits._left == node)
						node->_traits.parent->_traits._left = 0;
					else
						node->_traits.parent->_traits._right = 0;
				}
				else
					_root = 0;
			}

			//b steals the parent of a
			void	replace(node_pointer a, node_pointer b)
			{
				if (a == b)
					return ;
				b->_traits.parent = a->_traits.parent;
				if (a->_traits.parent)
				{
					if (a->_traits.parent->_traits._left == a)
						a->_traits.parent->_traits._left = b;
					else
						a->_traits.parent->_traits._right = b;
				}
				else
					_root = b;
			}

			//child swaps position with its parent
			void	_swapRelatedNodes(node_pointer child, node_pointer parent)
			{
				Traits	tmp;

				tmp = parent->_traits;
				//the child abdicates its parent parents
				replace(parent, child);
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
			void	_swapUnrelatedNodes(node_pointer a, node_pointer b)
			{
				Traits	tmp;

				tmp = b->_traits;
				//b adicates a's parent
				replace(a, b);
				//children swap
					//give the children of 'a' to the b
				b->_traits.left = a->_traits.left;
				b->_traits.right = a->_traits.right;
					//make the new children of b recognise b as their parent
				if (b->_traits.left)
					b->_traits.left->_traits._parent = b;
				if (b->_traits.right)
					b->_traits.right->_traits._parent = b;
					//get the children of b from the custodian and give them to 'a'
				a->_traits.left = tmp.left;
				a->_traits.right = tmp.right;
					//make the new children of 'a' recognise b as their parent
				if (a->_traits.left)
					a->_traits.left->_traits._parent = a;
				if (a->_traits.right)
					a->_traits.right->_traits._parent = a;
				//the exparent of b adopts a
				a->_traits.parent = tmp.parent;
				if (tmp.parent)
				{
					if (tmp.parent->_traits.left == b)
						a->_traits.parent->_traits._left = a;
					else
						a->_traits.parent->_traits._right = a;
				}
				else
					_root = a;
			}

			//a swaps position with b
			void	swap(node_pointer a, node_pointer b)
			{
				if (a->_traits.parent == b)
					_swapRelatedNodes(a, b);
				else if (b->_traits.parent == a)
					_swapRelatedNodes(b, a);
				else
					_swapUnrelatedNodes(a, b);
			}

			void	llRotate(node_pointer root)
			{
				node_pointer	newRoot;

				newRoot = root->_traits.left;

				//replace the current root with the newRoot
				replace(root, newRoot);
				
				//make the current root the right child of the newRoot
					//let the right child of the newRoot (current root) embrace its left child
				root->_traits.left = newRoot->_traits.right;
				if (root->_traits.left)
					root->_traits.left->_traits._parent = root;
					//let the newroot welcome its right child
				root->_traits.parent = newRoot;
				newRoot->_traits.right = root;

				//update the height of newRoot and its right child
				newRoot->_traits.right->updateHeight();
				newRoot->updateHeight();
			}

			void	rrRotate(node_pointer root)
			{
				node_pointer	newRoot;

				newRoot = root->_traits.right;

				//replace the current root with the newRoot
				replace(root, newRoot);
				
				//make the current root the left child of the newRoot
					//let the left child of the newRoot embrace its right child
				root->_traits.right = newRoot->_traits.left;
				if (root->_traits.right)
					root->_traits.right->_traits._parent = root;
					//let the newroot welcome its left child
				root->_traits.parent = newRoot;
				newRoot->_traits.left = root;
				
				//update the height of newRoot and its left child
				newRoot->_traits.left->updateHeight();
				newRoot->updateHeight();
			}

			void	lrRotate(node_pointer &root)
			{
				Node   *subRoot;

				subRoot = _traits.left->_traits._right;

				//replace the current node with the subRoot
				replace(root, subRoot);
				
				//adjsut the left child of the subRoot
					//let the left child of the subroot embrace its new right child
				_traits.left->_traits._right = subRoot->_traits.left;
				if (subRoot->_traits.left)
					subRoot->_traits.left->_traits._parent = _traits.left;
					//let the subroot welcome its left child
				subRoot->_traits.left = _traits.left;
				_traits.left->_traits._parent = subRoot;

				//adjust the right child of the subRoot
					//let the right child of the subroot embrace its new left child
				_traits.left = subRoot->_traits.right;
				if (_traits.left)
					_traits.left->_traits._parent = this;
					//let the subroot welcome its right child
				subRoot->_traits.right = this;
				_traits.parent = subRoot;

				//update the height of subRoot and its childs
				subRoot->_traits.left->updateHeight();
				subRoot->_traits.right->updateHeight();
				subRoot->updateHeight();
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Modifiers End
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
	/// Tree manipulation functions
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::insert(node_pointer &root, node_pointer node)
	{
		//if the node->value is greater than the 'this' value
		if (Compare(node->_value, _value))
		{
			if (_traits.left)
				_traits.left->insert(root, node);
			else
			{
				_traits.left = node;
				node->_traits.parent = this;
			}
		}
		//if the node->value is less than the 'this' value
		else if (Compare(_value, node->_value))
		{
			if (_traits.right)
				_traits.right->insert(root, node);
			else
			{
				_traits.right = node;
				node->_traits.parent = this;
			}
		}
		//if the node->value is equal to the 'this' value : leak possible here !!!!!!!!!!!!!!!!!!!!!
		else
			_value = node->_value;
		updateHeight();
		balance(root);
	}

	//delete a node from the tree
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::erase(node_pointer &root, value_type value)
	{
		node_pointer	parent;
		node_pointer	candidate;

		if (_value == value)
		{
			//the to-delete node has a both childs
			if (_traits.left && _traits.right)
			{
				std::cout << "looking for candidate" << std::endl;
				candidate = getInOrderSuccessor();
				std::cout << "candidate found : " << candidate->_value << std::endl;
				swap(root, candidate);
				candidate->updateHeight();
			}
			parent = _traits.parent;
			//the to-delete node has no children
			if (!_traits.left && !_traits.right)
				isolate(root);
			//the to-delete node has a left child only
			else if (_traits.left)
				replace(root, _traits.left);
			//the to-delete node has a right child only
			else if (_traits.right)
				replace(_traits.right);
			while (parent)
			{
				parent->updateHeight();
				parent->balance(root);
				parent = parent->_traits.parent;
			}
		}
		else if (_value < value)
		{
			if (_traits.right)
				_traits.right->erase(root, value);
		}
		else
		{
			if (_traits.left)
				_traits.left->erase(root, value);
		}
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::balance(node_pointer &root)
	{
		int balanceFactor;
		int subBalanceFactor;

		balanceFactor = getBalanceFactor();
		if (std::abs(balanceFactor) < 2)
			return ;
		if (balanceFactor < 0)
		{
			subBalanceFactor = _traits.right->getBalanceFactor();
			if (subBalanceFactor < 0)
				rrRotate(root);
			else if (subBalanceFactor > 0)
				rlRotate(root);
		}
		else
		{
			subBalanceFactor = _traits.left->getBalanceFactor();
			if (subBalanceFactor < 0)
				lrRotate(root);
			else if (subBalanceFactor > 0)
				llRotate(root);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Tree manipulation functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Nodes manipulation functions
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//node swaps position with 'this'
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::swap(node_pointer &root, node_pointer node)
	{
		bool	isleft;
		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;

		left = node->_traits.left;
		right = node->_traits.right;
		parent = node->_traits.parent;
		if (parent)
		{
			isleft = 0;
			if (node->_traits.parent->_traits._left == node)
				isleft = 1;
		}
		replace(node);
		if (parent == this)
		{
			if (isleft)
			{
				node->_traits.left = this;
				node->_traits.right = _traits.right;
				if (node->_traits.right)
					node->_traits.right->_traits._parent = node;
			}
			else
			{
				node->_traits.left = _traits.left;
				if (node->_traits.left)
					node->_traits.left->_traits._parent = node;
				node->_traits.right = this;
			}
			_traits.parent = node;
			_traits.left = left;
			if (left)
				left->_traits.parent = this;
			_traits.right = right;
			if (right)
				right->_traits.parent = this;
		}
		else
		{
			_traits.parent = parent;
			if (parent)
			{
				if (parent->_traits.left == node)
					_traits.parent->_traits._left = this;
				else
					_traits.parent->_traits._right = this;
			}
			else
				root = this;
			
			//children swap
				//give the children of 'this' to the node
			node->_traits.left = _traits.left;
			node->_traits.right = _traits.right;
				//make the new children of node recognise node as their parent
			if (node->_traits.left)
				node->_traits.left->_traits._parent = node;
			if (node->_traits.right)
				node->_traits.right->_traits._parent = node;
				//get the children of node from the custodian and give them to 'this'
			_traits.left = left;
			_traits.right = right;
				//make the new children of 'this' recognise node as their parent
			if (_traits.left)
				_traits.left->_traits._parent = this;
			if (_traits.right)
				_traits.right->_traits._parent = this;
		}
	}

	//node steals the parent of 'this'
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::replace(node_pointer &root, node_pointer node)
	{
		node->_traits.parent = _traits.parent;
		if (_traits.parent)
		{
			if (_traits.parent->_traits._left == this)
					_traits.parent->_traits._left = node;
			else
				_traits.parent->_traits._right = node;
		}
		else
			root = node;
	}

	//isolates a node from the rest of the tree (its parent does not recongnise him 'poor child')
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::isolate(node_pointer &root)
	{
		if (_traits.parent)
		{
			if (_traits.parent->_traits._left == this)
				_traits.parent->_traits._left = 0;
			else
				_traits.parent->_traits._right = 0;
		}
		else
			root = 0;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Nodes manipulation functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Rotations
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	void    Avl<T, Compare, Alloc>::Node::llRotate(node_pointer &root)
	{
		Node   *subRoot;

		subRoot = _traits.left;

		//replace the current node with the subRoot
		replace(root, subRoot);
		
		//make the current node the right child of the subRoot
			//let the right child of the subRoot embrace its left child
		_traits.left = subRoot->_traits.right;
		if (_traits.left)
			_traits.left->_traits._parent = this;
			//let the subroot welcome its right child
		_traits.parent = subRoot;
		subRoot->_traits.right = this;

		//update the height of subRoot and its right child
		subRoot->_traits.right->updateHeight();
		subRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void    Avl<T, Compare, Alloc>::Node::rrRotate(node_pointer &root)
	{
		Node   *subRoot;

		subRoot = _traits.right;

		//replace the current node with the subRoot
		replace(root, subRoot);
		
		//make the current node the left child of the subRoot
			//let the left child of the subRoot embrace its right child
		_traits.right = subRoot->_traits.left;
		if (_traits.right)
			_traits.right->_traits._parent = this;
			//let the subroot welcome its left child
		_traits.parent = subRoot;
		subRoot->_traits.left = this;
		
		//update the height of subRoot and its left child
		subRoot->_traits.left->updateHeight();
		subRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void    Avl<T, Compare, Alloc>::Node::lrRotate(node_pointer &root)
	{
		Node   *subRoot;

		subRoot = _traits.left->_traits._right;

		//replace the current node with the subRoot
		replace(root, subRoot);
		
		//adjsut the left child of the subRoot
			//let the left child of the subroot embrace its new right child
		_traits.left->_traits._right = subRoot->_traits.left;
		if (subRoot->_traits.left)
			subRoot->_traits.left->_traits._parent = _traits.left;
			//let the subroot welcome its left child
		subRoot->_traits.left = _traits.left;
		_traits.left->_traits._parent = subRoot;

		//adjust the right child of the subRoot
			//let the right child of the subroot embrace its new left child
		_traits.left = subRoot->_traits.right;
		if (_traits.left)
			_traits.left->_traits._parent = this;
			//let the subroot welcome its right child
		subRoot->_traits.right = this;
		_traits.parent = subRoot;

		//update the height of subRoot and its childs
		subRoot->_traits.left->updateHeight();
		subRoot->_traits.right->updateHeight();
		subRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void    Avl<T, Compare, Alloc>::Node::rlRotate(node_pointer &root)
	{
		Node   *subRoot;

		subRoot = _traits.right->_traits._left;

		//replace the current node with the subRoot
		replace(root, subRoot);
		
		//adjsut the right child of the subRoot
			//let the right child of the subroot embrace its new left child
		_traits.right->_traits._left = subRoot->_traits.right;
		if (subRoot->_traits.right)
			subRoot->_traits.right->_traits._parent = _traits.right;
			//let the subroot welcome its right child
		subRoot->_traits.right = _traits.right;
		_traits.right->_traits._parent = subRoot;

		//adjsut the left child of the subRoot
			//let the left child of the subroot embrace its new right child
		_traits.right = subRoot->_traits.left;
		if (_traits.right)
			_traits.right->_traits._parent = this;
			//let the subroot welcome its left child
		subRoot->_traits.left = this;
		_traits.parent = subRoot;

		//update the height of subRoot and its childs
		subRoot->_traits.left->updateHeight();
		subRoot->_traits.right->updateHeight();
		subRoot->updateHeight();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Rotations End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Status quo helper functions (do not change the tree nodes disposition)
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::updateHeight()
	{
		size_type	leftHeight;
		size_type	rightHeight;

		if (_traits.left)
			leftHeight =_traits.left->_traits._height;
		else
			leftHeight = 0;
		if (_traits.right)
			rightHeight =_traits.right->_traits._height;
		else
			rightHeight = 0;
		_traits.height = std::max(leftHeight, rightHeight) + 1;
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
			leftHeight =_traits.left->_traits._height + 1;
		else
			leftHeight = 0;
		if (_traits.right)
			rightHeight =_traits.right->_traits._height + 1;
		else
			rightHeight = 0;
		return leftHeight - rightHeight;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Status quo helper functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters End
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
	/// Getters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters
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
	/// Setters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// External
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Trunk
	{
		Trunk		*prev;
		std::string	str;
	
		Trunk(Trunk *prev, std::string str)
		{
			prev = prev;
			str = str;
		}
	};

	void showTrunks(std::ostream& ostr, Trunk *p);
	
	template<typename T, typename Compare, typename Alloc>
	void printTree(std::ostream& ostr, typename Avl<T, Compare, Alloc>::const_node_pointer root, Trunk *prev, bool isLeft)
	{
		if (root == nullptr) {
			return;
		}
	
		std::string prev_str = "    ";
		Trunk *trunk = new Trunk(prev, prev_str);
	
		printTree<T, Compare, Alloc>(ostr, root->getRight(), trunk, true);
	
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
		// ostr << " (" << root->getValue() << "|" << root->getLeftHeight() << "|" << root->getRightHeight() << ")" << std::endl;
		// ostr << " (" << root->getValue() << " | " << (root->getParent() ? root->getParent()->getValue() : -1) << ")" << std::endl;
		ostr << " " << root->getValue() << std::endl;
		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = "   |";
	
		printTree<T, Compare, Alloc>(ostr, root->getLeft(), trunk, false);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// External End
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Ostream operator << overload
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare, typename Alloc>
	std::ostream &operator<<(std::ostream& ostr, const Avl<T, Compare, Alloc>& tree)
	{
		ostr << "======================================================================================================================" << std::endl;
		printTree<T, Compare, Alloc>(ostr, tree._root, nullptr, false);
		ostr << "======================================================================================================================" << std::endl;
		return ostr;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Ostream operator << overload End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
}


#endif