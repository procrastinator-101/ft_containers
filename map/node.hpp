#ifndef NODE_HPP
# define NODE_HPP

#include <cstddef>
#include <algorithm>    // std::max
#include <string>    // Trunk
#include <iostream>    // cout

namespace ft
{
	template<typename T, typename Compare>
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
			typedef const T& const_reference;

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


		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			Node();
			~Node();

			Node(value_type value);
			Node(value_type value, node_pointer left, node_pointer right, node_pointer parent);

			Node(const Node& src);
			node_reference	operator=(const Node& rhs);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// destructors, constructors, and assignment operators End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Tree needed methods
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			void    updateHeight();
			int     getBalanceFactor() const;

			node_pointer	getInOrderSuccessor() const;
			node_pointer	getInOrderPredeccessor() const;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Tree needed methods End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Getters End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			value_type		getValue() const;
			size_type		getHeight() const;

			node_pointer	getLeft() const;//!!!!!! const_node_pointer 
			node_pointer	getRight() const;
			node_pointer	getParent() const;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Getters End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Setters End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			void	setValue(value_type value);
			void	setHeight(size_type height);

			void	setLeft(node_pointer left);
			void	setRight(node_pointer right);
			void	setParent(node_pointer parent);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Setters End
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// attributes
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		public:
			value_type	_value;
			Traits		_traits;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/// attributes End
		/////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare>
	Node<T, Compare>::Node() :  _value(), _traits()//!!!!!!!
	{
	}

	template<typename T, typename Compare>
	Node<T, Compare>::~Node()
	{
	}

	template<typename T, typename Compare>
	Node<T, Compare>::Node(value_type value, node_pointer left, node_pointer right, node_pointer parent) : _value(value), _traits(left, right, parent)
	{
	}

	template<typename T, typename Compare>
	Node<T, Compare>::Node(const Node& src) : _value(src._value), _traits(src._traits)
	{
	}

	template<typename T, typename Compare>
	Node<T, Compare>::Node(value_type value) : _value(value), _traits()//!!!!
	{
	}

	template<typename T, typename Compare>
	typename Node<T, Compare>::node_reference	Node<T, Compare>::operator=(const Node& rhs)
	{
		_value = rhs._value;
		_traits = rhs._traits;
		return *this;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// destructors, constructors, and assignment operators
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Tree needed methods
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare>
	void	Node<T, Compare>::updateHeight()
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

	template<typename T, typename Compare>
	typename Node<T, Compare>::node_pointer	Node<T, Compare>::getInOrderSuccessor() const
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

	template<typename T, typename Compare>
	typename Node<T, Compare>::node_pointer	Node<T, Compare>::getInOrderPredeccessor() const
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

	template<typename T, typename Compare>
	int	Node<T, Compare>::getBalanceFactor() const
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
	/// Tree needed methods
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare>
	typename Node<T, Compare>::value_type	Node<T, Compare>::getValue() const
	{
		return _value;
	}

	template<typename T, typename Compare>
	typename Node<T, Compare>::size_type	Node<T, Compare>::getHeight() const
	{
		return _traits.height;
	}

	template<typename T, typename Compare>
	typename Node<T, Compare>::node_pointer	Node<T, Compare>::getLeft() const
	{
		return _traits.left;
	}

	template<typename T, typename Compare>
	typename Node<T, Compare>::node_pointer	Node<T, Compare>::getRight() const
	{
		return _traits.right;
	}

	template<typename T, typename Compare>
	typename Node<T, Compare>::node_pointer	Node<T, Compare>::getParent() const
	{
		return _traits.parent;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters End
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, typename Compare>
	void	Node<T, Compare>::setValue(value_type value)
	{
		_value = value;
	}

	template<typename T, typename Compare>
	void	Node<T, Compare>::setHeight(size_type height)
	{
		_traits.height = height;
	}

	template<typename T, typename Compare>
	void	Node<T, Compare>::setLeft(node_pointer left)
	{
		_traits.left = left;
	}

	template<typename T, typename Compare>
	void	Node<T, Compare>::setRight(node_pointer right)
	{
		_traits.right = right;
	}

	template<typename T, typename Compare>
	void	Node<T, Compare>::setParent(node_pointer parent)
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
	
		Trunk(Trunk *aprev, std::string astr)
		{
			prev = aprev;
			str = astr;
		}
	};
	void showTrunks(std::ostream& ostr, Trunk *p);

	template<typename T, typename Compare>
	void	printTree(std::ostream& ostr, Node<T, Compare> *root, Trunk *prev, bool isLeft)
	{
		if (root == 0) {
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
		delete trunk;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/// External End
/////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif