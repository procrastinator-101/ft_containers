#ifndef AVL_HPP
# define AVL_HPP

#include <cstdlib>
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
							node_pointer	_left;
							node_pointer	_right;
							node_pointer	_parent;

							size_type		_height;
						
						public:
							Traits() : _left(0), _right(0), _parent(0), _height(0)
							{
							}

							Traits(node_pointer left, node_pointer right, node_pointer parent, size_type height) : _left(left), _right(right), _parent(parent), _height(height)
							{
							}

							Traits(const Traits& src) : _left(src._left), _right(src._right), _parent(src._parent), _height(src._height)
							{
							}

							Traits	&operator=(const Traits& rop)
							{
								if (this == &rop)
									return *this;
								_left = rop._left;
								_right = rop._right;
								_parent = rop._parent;
								_height = rop._height;
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

			void	insert(const value_type& val)
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
				if (_root)
					_root->insert(_root, node);
				else
					_root = node;
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
		this->_value = rhs._value;
		this->_traits = rhs._traits;
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
		if (this->_value == node->_value)
			return;
		else if (this->_value < node->_value)
		{
			if (this->_traits._right)
				this->_traits._right->insert(root, node);
			else
			{
				this->_traits._right = node;
				node->_traits._parent = this;
			}
		}
		else
		{
			if (this->_traits._left)
				this->_traits._left->insert(root, node);
			else
			{
				this->_traits._left = node;
				node->_traits._parent = this;
			}
		}
		this->updateHeight();
		this->balance(root);
	}

	//delete a node from the tree
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::erase(node_pointer &root, value_type value)
	{
		node_pointer	parent;
		node_pointer	candidate;

		if (this->_value == value)
		{
			//the to-delete node has a both childs
			if (this->_traits._left && this->_traits._right)
			{
				std::cout << "looking for candidate" << std::endl;
				candidate = this->getInOrderSuccessor();
				std::cout << "candidate found : " << candidate->_value << std::endl;
				this->swap(root, candidate);
				candidate->updateHeight();
			}
			parent = this->_traits._parent;
			//the to-delete node has no children
			if (!this->_traits._left && !this->_traits._right)
				this->isolate(root);
			//the to-delete node has a left child only
			else if (this->_traits._left)
				this->replace(root, this->_traits._left);
			//the to-delete node has a right child only
			else if (this->_traits._right)
				this->replace(this->_traits._right);
			while (parent)
			{
				parent->updateHeight();
				parent->balance(root);
				parent = parent->_traits._parent;
			}
		}
		else if (this->_value < value)
		{
			if (this->_traits.right)
				this->_traits._right->erase(root, value);
		}
		else
		{
			if (this->_traits._left)
				this->_traits._left->erase(root, value);
		}
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::balance(node_pointer &root)
	{
		int balanceFactor;
		int subBalanceFactor;

		balanceFactor = this->getBalanceFactor();
		if (std::abs(balanceFactor) < 2)
			return ;
		if (balanceFactor < 0)
		{
			subBalanceFactor = _traits._right->getBalanceFactor();
			if (subBalanceFactor < 0)
				rrRotate(root);
			else if (subBalanceFactor > 0)
				rlRotate(root);
		}
		else
		{
			subBalanceFactor = _traits._left->getBalanceFactor();
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

		left = node->_traits._left;
		right = node->_traits._right;
		parent = node->_traits._parent;
		if (parent)
		{
			isleft = 0;
			if (node->_traits._parent->_traits._left == node)
				isleft = 1;
		}
		this->replace(node);
		if (parent == this)
		{
			if (isleft)
			{
				node->_traits._left = this;
				node->_traits._right = this->_traits._right;
				if (node->_traits._right)
					node->_traits._right->_traits._parent = node;
			}
			else
			{
				node->_traits._left = this->_traits._left;
				if (node->_traits._left)
					node->_traits._left->_traits._parent = node;
				node->_traits._right = this;
			}
			this->_traits._parent = node;
			this->_traits._left = left;
			if (left)
				left->_traits._parent = this;
			this->_traits._right = right;
			if (right)
				right->_traits._parent = this;
		}
		else
		{
			this->_traits._parent = parent;
			if (parent)
			{
				if (parent->_traits._left == node)
					this->_traits._parent->_traits._left = this;
				else
					this->_traits._parent->_traits._right = this;
			}
			else
				root = this;
			
			//children swap
				//give the children of 'this' to the node
			node->_traits._left = this->_traits._left;
			node->_traits._right = this->_traits._right;
				//make the new children of node recognise node as their parent
			if (node->_traits._left)
				node->_traits._left->_traits._parent = node;
			if (node->_traits._right)
				node->_traits._right->_traits._parent = node;
				//get the children of node from the custodian and give them to 'this'
			this->_traits._left = left;
			this->_traits._right = right;
				//make the new children of 'this' recognise node as their parent
			if (this->_traits._left)
				this->_traits._left->_traits._parent = this;
			if (this->_traits._right)
				this->_traits._right->_traits._parent = this;
		}
	}

	//node steals the parent of 'this'
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::replace(node_pointer &root, node_pointer node)
	{
		node->_traits._parent = this->_traits._parent;
		if (this->_traits._parent)
		{
			if (this->_traits._parent->_traits._left == this)
					this->_traits._parent->_traits._left = node;
			else
				this->_traits._parent->_traits._right = node;
		}
		else
			root = node;
	}

	//isolates a node from the rest of the tree (its parent does not recongnise him 'poor child')
	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::isolate(node_pointer &root)
	{
		if (this->_traits._parent)
		{
			if (this->_traits._parent->_traits._left == this)
				this->_traits._parent->_traits._left = 0;
			else
				this->_traits._parent->_traits._right = 0;
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

		subRoot = this->_traits._left;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//make the current node the right child of the subRoot
			//let the right child of the subRoot embrace its left child
		this->_traits._left = subRoot->_traits._right;
		if (this->_traits._left)
			this->_traits._left->_traits._parent = this;
			//let the subroot welcome its right child
		this->_traits._parent = subRoot;
		subRoot->_traits._right = this;

		//update the height of subRoot and its right child
		subRoot->_traits._right->updateHeight();
		subRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void    Avl<T, Compare, Alloc>::Node::rrRotate(node_pointer &root)
	{
		Node   *subRoot;

		subRoot = this->_traits._right;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//make the current node the left child of the subRoot
			//let the left child of the subRoot embrace its right child
		this->_traits._right = subRoot->_traits._left;
		if (this->_traits._right)
			this->_traits._right->_traits._parent = this;
			//let the subroot welcome its left child
		this->_traits._parent = subRoot;
		subRoot->_traits._left = this;
		
		//update the height of subRoot and its left child
		subRoot->_traits._left->updateHeight();
		subRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void    Avl<T, Compare, Alloc>::Node::lrRotate(node_pointer &root)
	{
		Node   *subRoot;

		subRoot = this->_traits._left->_traits._right;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//adjsut the left child of the subRoot
			//let the left child of the subroot embrace its new right child
		this->_traits._left->_traits._right = subRoot->_traits._left;
		if (subRoot->_traits._left)
			subRoot->_traits._left->_traits._parent = this->_traits._left;
			//let the subroot welcome its left child
		subRoot->_traits._left = this->_traits._left;
		this->_traits._left->_traits._parent = subRoot;

		//adjust the right child of the subRoot
			//let the right child of the subroot embrace its new left child
		this->_traits._left = subRoot->_traits._right;
		if (this->_traits._left)
			this->_traits._left->_traits._parent = this;
			//let the subroot welcome its right child
		subRoot->_traits._right = this;
		this->_traits._parent = subRoot;

		//update the height of subRoot and its childs
		subRoot->_traits._left->updateHeight();
		subRoot->_traits._right->updateHeight();
		subRoot->updateHeight();
	}

	template<typename T, typename Compare, typename Alloc>
	void    Avl<T, Compare, Alloc>::Node::rlRotate(node_pointer &root)
	{
		Node   *subRoot;

		subRoot = this->_traits._right->_traits._left;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//adjsut the right child of the subRoot
			//let the right child of the subroot embrace its new left child
		this->_traits._right->_traits._left = subRoot->_traits._right;
		if (subRoot->_traits._right)
			subRoot->_traits._right->_traits._parent = this->_traits._right;
			//let the subroot welcome its right child
		subRoot->_traits._right = this->_traits._right;
		this->_traits._right->_traits._parent = subRoot;

		//adjsut the left child of the subRoot
			//let the left child of the subroot embrace its new right child
		this->_traits._right = subRoot->_traits._left;
		if (this->_traits._right)
			this->_traits._right->_traits._parent = this;
			//let the subroot welcome its left child
		subRoot->_traits._left = this;
		this->_traits._parent = subRoot;

		//update the height of subRoot and its childs
		subRoot->_traits._left->updateHeight();
		subRoot->_traits._right->updateHeight();
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

		if (_traits._left)
			leftHeight =_traits._left->_traits._height;
		else
			leftHeight = 0;
		if (_traits._right)
			rightHeight =_traits._right->_traits._height;
		else
			rightHeight = 0;
		_traits._height = std::max(leftHeight, rightHeight) + 1;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getInOrderSuccessor() const
	{
		node_pointer	ret;

		//the smallest key that is larger than x

		ret = 0;
		//left most child of its right suNode
		if (this->_traits._right)
		{
			ret = this->_traits._right;
			while (ret->_traits._left)
				ret = ret->_traits._left;
		}
		//first parent with a key larger than that of the current node
		else
		{
			ret = this->_traits._parent;
			while (ret && ret->_value < this->_value)
				ret = ret->_traits._parent;
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
		if (this->_traits._left)
		{
			ret = this->_traits._left;
			while (ret->_traits._right)
				ret = ret->_traits._right;
		}
		//first parent with a key samller than that of the current node
		else
		{
			ret = this->_traits._parent;
			while (ret && ret->_value > this->_value)
				ret = ret->_traits._parent;
		}
		return ret;
	}

	template<typename T, typename Compare, typename Alloc>
	int	Avl<T, Compare, Alloc>::Node::getBalanceFactor() const
	{
		size_type	leftHeight;
		size_type	rightHeight;

		if (_traits._left)
			leftHeight =_traits._left->_traits._height + 1;
		else
			leftHeight = 0;
		if (_traits._right)
			rightHeight =_traits._right->_traits._height + 1;
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
		return this->_value;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::size_type	Avl<T, Compare, Alloc>::Node::getHeight() const
	{
		return _traits._height;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getLeft() const
	{
		return this->_traits._left;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getRight() const
	{
		return this->_traits._right;
	}

	template<typename T, typename Compare, typename Alloc>
	typename Avl<T, Compare, Alloc>::Node::node_pointer	Avl<T, Compare, Alloc>::Node::getParent() const
	{
		return this->_traits._parent;
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
		this->_value = value;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setHeight(size_type height)
	{
		_traits._height = height;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setLeft(node_pointer left)
	{
		this->_left = left;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setRight(node_pointer right)
	{
		this->_right = right;
	}

	template<typename T, typename Compare, typename Alloc>
	void	Avl<T, Compare, Alloc>::Node::setParent(node_pointer parent)
	{
		this->_traits._parent = parent;
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
			this->prev = prev;
			this->str = str;
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