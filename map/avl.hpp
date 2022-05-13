#ifndef AVL_HPP
# define AVL_HPP

#include <iostream>

namespace ft
{
	template<typename T, typename Compare, typename Alloc>
	class Avl
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Node class Forward declaration
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			class Node;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Node class Forward declaration End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			typedef Compare value_compare;
			typedef T value_type;

			typedef Alloc allocator_type;
			typedef typename allocator_type::template rebind<Node>::other node_allocator_type;

			typedef Node* pointer;
			typedef const Node* const_pointer;
			typedef Node& reference;
			typedef const Node& const_reference;

			typedef size_t size_type;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// type definitions End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			Avl() : _root(0)
			{
			}

			Avl(pointer root) : _root(root)
			{
			}

			Avl(const Avl& src) : _root(0), _allocator(src._allocator), _nodeAllocator(src._nodeAllocator)
			{
				// pointer	tmp;
				// pointer node;

				// try
				// {
				// 	for (node = src._root; node; node = node->getInOrderSuccessor())
				// 	{
						
				// 		node->insert(_root, node);
				// 	}
				// }
				// catch
				// {

				// }
			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		private:
			pointer	_root;
			allocator_type	_allocator;
			node_allocator_type	_nodeAllocator;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// private data members End
		/////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Node class Defintion
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// private:
		public:
			class Node
			{
				private:
					/////////////////////////////////////////////////////////////////////////////////////////////////////
					/// Traits class Defintion
					/////////////////////////////////////////////////////////////////////////////////////////////////////
					class Traits
					{
						private:
							pointer		_left;
							pointer		_right;
							pointer		_parent;

							size_type	_height;
						
						public:
							Traits() : _left(0), _right(0), _parent(0), _height(0)
							{
							}

							Traits(pointer left, pointer right, pointer parent, size_type height) : _left(left), _right(right), _parent(parent), _height(height)
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
				private:

					value_type	_value;
					Traits		_traits;


					void	isolate(pointer &root);
					void	swap(pointer &root, pointer node);
					void	replace(pointer &root, pointer node);

					void    balance(pointer &root);

					void    llRotate(pointer &root);
					void    lrRotate(pointer &root);
					void    rlRotate(pointer &root);
					void    rrRotate(pointer &root);

					void    updateCounts();

					int     getBalanceFactor() const;


				public:

					Node();
					~Node();

					Node(value_type value);
					Node(value_type value, pointer left, pointer right, pointer parent);

					Node(const Node& src);
					reference	operator=(const Node& rhs);

					void	erase(pointer &root, value_type value);
					void	insert(pointer &root, reference node);

					pointer	getInOrderSuccessor() const;
					pointer	getInOrderPredeccessor() const;

					value_type		getValue() const;
					size_type		getLeftHeight() const;
					size_type		getRightHeight() const;

					pointer	getLeft() const;
					pointer	getRight() const;
					pointer	getParent() const;

					void	setValue(value_type value);
					void	setLeftHeight(size_type leftHeight);
					void	setRightHeight(size_type rightHeight);

					void	setLeft(pointer left);
					void	setRight(pointer right);
					void	setParent(pointer parent);
			};
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Node class Defintion End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::Node() :  _value(), _traits()
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::~Node()
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::Node(value_type value, pointer left, pointer right, pointer parent) : _value(value), _traits(left, right, parent)
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::Node(const Node& src) : _value(src._value), _traits(src._traits)
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::Node(value_type value) : _value(value), _traits()
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::reference	Avl<value_type, value_compare, Alloc>::Node::operator=(const Node& rhs)
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
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::insert(pointer &root, reference node)
	{
		if (this->_value == node._value)
			return;
		else if (this->_value < node._value)
		{
			if (this->_traits._right)
				this->_traits._right->insert(node);
			else
			{
				this->_traits._right = &node;
				node._traits._parent = this;
			}
		}
		else
		{
			if (this->_traits._left)
				this->_traits._left->insert(node);
			else
			{
				this->_traits._left = &node;
				node._traits._parent = this;
			}
		}
		this->updateCounts();
		this->balance(root);
	}

	//delete a node from the tree
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::erase(pointer &root, value_type value)
	{
		pointer	parent;
		pointer	candidate;

		if (this->_value == value)
		{
			//the to-delete node has a both childs
			if (this->_traits._left && this->_traits._right)
			{
				std::cout << "looking for candidate" << std::endl;
				candidate = this->getInOrderSuccessor();
				std::cout << "candidate found : " << candidate->_value << std::endl;
				this->swap(root, candidate);
				candidate->updateCounts();
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
				parent->updateCounts();
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

	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::balance(pointer &root)
	{
		int balanceFactor;
		int subBalanceFactor;

		balanceFactor = this->getBalanceFactor();
		if (abs(balanceFactor) < 2)
			return ;
		if (balanceFactor < 0)
		{
			subBalanceFactor = this->_right->getBalanceFactor();
			if (subBalanceFactor < 0)
				this->rrRotate(root);
			else if (subBalanceFactor > 0)
				this->rlRotate(root);
		}
		else
		{
			subBalanceFactor = this->_left->getBalanceFactor();
			if (subBalanceFactor < 0)
				this->lrRotate(root);
			else if (subBalanceFactor > 0)
				this->llRotate(root);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Tree manipulation functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Nodes manipulation functions
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//node swaps position with 'this'
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::swap(pointer &root, pointer node)
	{
		bool	isleft;
		pointer	left;
		pointer	right;
		pointer	parent;

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
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::replace(pointer &root, pointer node)
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
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::isolate(pointer &root)
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
	template<typename value_type, typename value_compare, typename Alloc>
	void    Avl<value_type, value_compare, Alloc>::Node::llRotate(pointer &root)
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
		subRoot->_traits._right->updateCounts();
		subRoot->updateCounts();
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void    Avl<value_type, value_compare, Alloc>::Node::rrRotate(pointer &root)
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
		subRoot->_traits._left->updateCounts();
		subRoot->updateCounts();
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void    Avl<value_type, value_compare, Alloc>::Node::lrRotate(pointer &root)
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
		subRoot->_traits._left->updateCounts();
		subRoot->_traits._right->updateCounts();
		subRoot->updateCounts();
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void    Avl<value_type, value_compare, Alloc>::Node::rlRotate(pointer &root)
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
		subRoot->_traits._left->updateCounts();
		subRoot->_traits._right->updateCounts();
		subRoot->updateCounts();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Rotations End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Status quo helper functions (do not change the tree nodes disposition)
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::updateCounts()
	{
		if (this->_traits._left)
			this->_traits._leftHeight = std::max(this->_traits._left->_traits._leftHeight, this->_traits._left->_traits._rightHeight) + 1;
		else
			this->_traits._leftHeight = 0;
		if (this->_traits._right)
			this->_traits._rightHeight = std::max(this->_traits._right->_traits._leftHeight, this->_traits._right->_traits._rightHeight) + 1;
		else
			this->_traits._rightHeight = 0;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getInOrderSuccessor() const
	{
		pointer	ret;

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

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getInOrderPredeccessor() const
	{
		pointer	ret;

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

	template<typename value_type, typename value_compare, typename Alloc>
	int	Avl<value_type, value_compare, Alloc>::Node::getBalanceFactor() const
	{
		if (_traits._leftHeight > _traits._rightHeight)
			return _traits._leftHeight - _traits._rightHeight;
		return _traits._rightHeight - _traits._leftHeight;;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Status quo helper functions End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::value_type	Avl<value_type, value_compare, Alloc>::Node::getValue() const
	{
		return this->_value;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::size_type	Avl<value_type, value_compare, Alloc>::Node::getLeftHeight() const
	{
		return this->_traits._leftHeight;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::size_type	Avl<value_type, value_compare, Alloc>::Node::getRightHeight() const
	{
		return this->_traits._rightHeight;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getLeft() const
	{
		return this->_traits._left;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getRight() const
	{
		return this->_traits._right;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getParent() const
	{
		return this->_traits._parent;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::setValue(value_type value)
	{
		this->_value = value;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::setLeftHeight(size_type leftHeight)
	{
		this->_leftHeight = leftHeight;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::setRightHeight(size_type rightHeight)
	{
		this->_rightHeight = rightHeight;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::setLeft(pointer left)
	{
		this->_left = left;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::setRight(pointer right)
	{
		this->_right = right;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::setParent(pointer parent)
	{
		this->_traits._parent = parent;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Ostream operator << overload
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename value_type, typename value_compare, typename Alloc>
	std::ostream &operator<<(std::ostream& ostr, typename Avl<value_type, value_compare, Alloc>::pointer root)
	{
		ostr << "======================================================================================================================" << std::endl;
		printTree(ostr, &root, nullptr, false);
		ostr << "======================================================================================================================" << std::endl;
		return ostr;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Ostream operator << overload End
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
	
	template<typename value_type, typename value_compare, typename Alloc>
	void printTree(std::ostream& ostr, typename Avl<value_type, value_compare, Alloc>::pointer root, Trunk *prev, bool isLeft)
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
		// ostr << " (" << root->getValue() << "|" << root->getLeftHeight() << "|" << root->getRightHeight() << ")" << std::endl;
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
}


#endif