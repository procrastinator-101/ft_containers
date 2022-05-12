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
		Avl() : _root(0)
		{
		}

		Avl(pointer root) : _root(root)
		{
		}

		Avl(const Avl& src) : _root(0)
		{
			pointer	tmp;
			pointer node;

			try
			{
				for (node = src._root; node; node = node->getInOrderSuccessor())
				{
					
					node->insert(_root, node);
				}
			}
			catch
			{

			}
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
		private:
			class Node
			{
				private:

					value_type	_value;
					size_type	_leftHeight;
					size_type	_rightHeight;

					pointer		_left;
					pointer		_right;
					pointer		_parent;


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
	Avl<value_type, value_compare, Alloc>::Node::Node() : _value(value_type()), _leftHeight(0), _rightHeight(0), _left(0), _right(0), _parent(0)
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::~Node()
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::Node(value_type value, pointer left, pointer right, pointer parent) : _value(value), _leftHeight(0), _rightHeight(0), _left(left), _right(right), _parent(parent)
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::Node(const Node& src) : _value(src._value), _leftHeight(src._leftHeight), _rightHeight(src._rightHeight), _left(src._left), _right(src._right), _parent(src._parent)
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	Avl<value_type, value_compare, Alloc>::Node::Node(value_type value) : _value(value), _leftHeight(0), _rightHeight(0), _left(0), _right(0), _parent(0)
	{
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::reference	Avl<value_type, value_compare, Alloc>::Node::operator=(const Node& rhs)
	{
		this->_value = rhs._value;
		this->_leftHeight = rhs._leftHeight;
		this->_rightHeight = rhs._rightHeight;

		this->_left = rhs._left;
		this->_right = rhs._right;
		this->_parent = rhs._parent;
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
			if (this->_right)
				this->_right->insert(node);
			else
			{
				this->_right = &node;
				node._parent = this;
			}
		}
		else
		{
			if (this->_left)
				this->_left->insert(node);
			else
			{
				this->_left = &node;
				node._parent = this;
			}
		}
		this->updateCounts();
		this->balance(root);
	}

	//delete a node from the tree
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::erase(pointer &root, value_type value)
	{
		Node	*parent;
		Node	*candidate;

		if (this->_value == value)
		{
			//the to-delete node has a both childs
			if (this->_left && this->_right)
			{
				std::cout << "looking for candidate" << std::endl;
				candidate = this->getInOrderSuccessor();
				std::cout << "candidate found : " << candidate->_value << std::endl;
				this->swap(root, candidate);
				candidate->updateCounts();
			}
			parent = this->_parent;
			//the to-delete node has no children
			if (!this->_left && !this->_right)
				this->isolate(root);
			//the to-delete node has a left child only
			else if (this->_left)
				this->replace(root, this->_left);
			//the to-delete node has a right child only
			else if (this->_right)
				this->replace(this->_right);
			while (parent)
			{
				parent->updateCounts();
				parent->balance(root);
				parent = parent->_parent;
			}
		}
		else if (this->_value < value)
		{
			if (this->_right)
				this->_right->erase(root, value);
		}
		else
		{
			if (this->_left)
				this->_left->erase(root, value);
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
		Node	*left;
		Node	*right;
		Node	*parent;

		left = node->_left;
		right = node->_right;
		parent = node->_parent;
		if (parent)
		{
			isleft = 0;
			if (node->_parent->_left == node)
				isleft = 1;
		}
		this->replace(node);
		if (parent == this)
		{
			if (isleft)
			{
				node->_left = this;
				node->_right = this->_right;
				if (node->_right)
					node->_right->_parent = node;
			}
			else
			{
				node->_left = this->_left;
				if (node->_left)
					node->_left->_parent = node;
				node->_right = this;
			}
			this->_parent = node;
			this->_left = left;
			if (left)
				left->_parent = this;
			this->_right = right;
			if (right)
				right->_parent = this;
		}
		else
		{
			this->_parent = parent;
			if (parent)
			{
				if (parent->_left == node)
					this->_parent->_left = this;
				else
					this->_parent->_right = this;
			}
			else
				root = this;
			
			//children swap
				//give the children of 'this' to the node
			node->_left = this->_left;
			node->_right = this->_right;
				//make the new children of node recognise node as their parent
			if (node->_left)
				node->_left->_parent = node;
			if (node->_right)
				node->_right->_parent = node;
				//get the children of node from the custodian and give them to 'this'
			this->_left = left;
			this->_right = right;
				//make the new children of 'this' recognise node as their parent
			if (this->_left)
				this->_left->_parent = this;
			if (this->_right)
				this->_right->_parent = this;
		}
	}

	//node steals the parent of 'this'
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::replace(pointer &root, pointer node)
	{
		node->_parent = this->_parent;
		if (this->_parent)
		{
			if (this->_parent->_left == this)
					this->_parent->_left = node;
			else
				this->_parent->_right = node;
		}
		else
			root = node;
	}

	//isolates a node from the rest of the tree (its parent does not recongnise him 'poor child')
	template<typename value_type, typename value_compare, typename Alloc>
	void	Avl<value_type, value_compare, Alloc>::Node::isolate(pointer &root)
	{
		if (this->_parent)
		{
			if (this->_parent->_left == this)
				this->_parent->_left = 0;
			else
				this->_parent->_right = 0;
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

		subRoot = this->_left;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//make the current node the right child of the subRoot
			//let the right child of the subRoot embrace its left child
		this->_left = subRoot->_right;
		if (this->_left)
			this->_left->_parent = this;
			//let the subroot welcome its right child
		this->_parent = subRoot;
		subRoot->_right = this;

		//update the height of subRoot and its right child
		subRoot->_right->updateCounts();
		subRoot->updateCounts();
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void    Avl<value_type, value_compare, Alloc>::Node::rrRotate(pointer &root)
	{
		Node   *subRoot;

		subRoot = this->_right;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//make the current node the left child of the subRoot
			//let the left child of the subRoot embrace its right child
		this->_right = subRoot->_left;
		if (this->_right)
			this->_right->_parent = this;
			//let the subroot welcome its left child
		this->_parent = subRoot;
		subRoot->_left = this;
		
		//update the height of subRoot and its left child
		subRoot->_left->updateCounts();
		subRoot->updateCounts();
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void    Avl<value_type, value_compare, Alloc>::Node::lrRotate(pointer &root)
	{
		Node   *subRoot;

		subRoot = this->_left->_right;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//adjsut the left child of the subRoot
			//let the left child of the subroot embrace its new right child
		this->_left->_right = subRoot->_left;
		if (subRoot->_left)
			subRoot->_left->_parent = this->_left;
			//let the subroot welcome its left child
		subRoot->_left = this->_left;
		this->_left->_parent = subRoot;

		//adjust the right child of the subRoot
			//let the right child of the subroot embrace its new left child
		this->_left = subRoot->_right;
		if (this->_left)
			this->_left->_parent = this;
			//let the subroot welcome its right child
		subRoot->_right = this;
		this->_parent = subRoot;

		//update the height of subRoot and its childs
		subRoot->_left->updateCounts();
		subRoot->_right->updateCounts();
		subRoot->updateCounts();
	}

	template<typename value_type, typename value_compare, typename Alloc>
	void    Avl<value_type, value_compare, Alloc>::Node::rlRotate(pointer &root)
	{
		Node   *subRoot;

		subRoot = this->_right->_left;

		//replace the current node with the subRoot
		this->replace(root, subRoot);
		
		//adjsut the right child of the subRoot
			//let the right child of the subroot embrace its new left child
		this->_right->_left = subRoot->_right;
		if (subRoot->_right)
			subRoot->_right->_parent = this->_right;
			//let the subroot welcome its right child
		subRoot->_right = this->_right;
		this->_right->_parent = subRoot;

		//adjsut the left child of the subRoot
			//let the left child of the subroot embrace its new right child
		this->_right = subRoot->_left;
		if (this->_right)
			this->_right->_parent = this;
			//let the subroot welcome its left child
		subRoot->_left = this;
		this->_parent = subRoot;

		//update the height of subRoot and its childs
		subRoot->_left->updateCounts();
		subRoot->_right->updateCounts();
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
		if (this->_left)
			this->_leftHeight = std::max(this->_left->_leftHeight, this->_left->_rightHeight) + 1;
		else
			this->_leftHeight = 0;
		if (this->_right)
			this->_rightHeight = std::max(this->_right->_leftHeight, this->_right->_rightHeight) + 1;
		else
			this->_rightHeight = 0;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getInOrderSuccessor() const
	{
		Node	*ret;

		//the smallest key that is larger than x

		ret = 0;
		//left most child of its right suNode
		if (this->_right)
		{
			ret = this->_right;
			while (ret->_left)
				ret = ret->_left;
		}
		//first parent with a key larger than that of the current node
		else
		{
			ret = this->_parent;
			while (ret && ret->_value < this->_value)
				ret = ret->_parent;
		}
		return ret;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getInOrderPredeccessor() const
	{
		Node	*ret;

		//the largest key that is smaller than x

		ret = 0;
		//right most child of its left suNode
		if (this->_left)
		{
			ret = this->_left;
			while (ret->_right)
				ret = ret->_right;
		}
		//first parent with a key samller than that of the current node
		else
		{
			ret = this->_parent;
			while (ret && ret->_value > this->_value)
				ret = ret->_parent;
		}
		return ret;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	int	Avl<value_type, value_compare, Alloc>::Node::getBalanceFactor() const
	{
		if (_leftHeight > _rightHeight)
			return _leftHeight - _rightHeight;
		return _rightHeight - _leftHeight;;
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
		return this->_leftHeight;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::size_type	Avl<value_type, value_compare, Alloc>::Node::getRightHeight() const
	{
		return this->_rightHeight;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getLeft() const
	{
		return this->_left;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getRight() const
	{
		return this->_right;
	}

	template<typename value_type, typename value_compare, typename Alloc>
	typename Avl<value_type, value_compare, Alloc>::pointer	Avl<value_type, value_compare, Alloc>::Node::getParent() const
	{
		return this->_parent;
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
		this->_parent = parent;
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