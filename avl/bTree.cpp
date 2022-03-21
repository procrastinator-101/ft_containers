#include "bTree.hpp"


bTree::bTree() : _value(0), _leftHeight(0), _rightHeight(0), _left(0), _right(0), _parent(0)
{
}

bTree::~bTree()
{
}

bTree::bTree(int value, bTree *left, bTree *right, bTree *parent) : _value(value), _leftHeight(0), _rightHeight(0), _left(left), _right(right), _parent(parent)
{
}

bTree::bTree(const bTree& src) : _value(src._value), _leftHeight(src._leftHeight), _rightHeight(src._rightHeight), _left(src._left), _right(src._right), _parent(src._parent)
{
}

bTree::bTree(int value) : _value(value), _leftHeight(0), _rightHeight(0), _left(0), _right(0), _parent(0)
{
}

bTree   &bTree::operator=(const bTree& rhs)
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
/// Tree manipulation functions
/////////////////////////////////////////////////////////////////////////////////////////////////////

void    bTree::insert(bTree& node)
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
	this->balance();
}

//delete a node from the tree
void    bTree::erase(int value)
{
	bTree	*parent;
	bTree	*candidate;

	if (this->_value == value)
	{
		//the to-delete node has a both childs
		if (this->_left && this->_right)
		{
			candidate = this->getInOrderSuccessor();
			this->swap(candidate);
			candidate->updateCounts();
		}
		parent = this->_parent;
		//the to-delete node has no children
		if (!this->_left && !this->_right)
			this->isolate();
		//the to-delete node has a left child only
		else if (this->_left)
			this->replace(this->_left);
		//the to-delete node has a right child only
		else if (this->_right)
			this->replace(this->_right);
		while (parent)
		{
			parent->updateCounts();
			parent->balance();
			parent = parent->_parent;
		}
	}
	else if (this->_value < value)
	{
		if (this->_right)
			this->_right->erase(value);
	}
	else
	{
		if (this->_left)
			this->_left->erase(value);
	}
}

void    bTree::balance()
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
			this->rrRotate();
		else if (subBalanceFactor > 0)
			this->rlRotate();
	}
	else
	{
		subBalanceFactor = this->_left->getBalanceFactor();
		if (subBalanceFactor < 0)
			this->lrRotate();
		else if (subBalanceFactor > 0)
			this->llRotate();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Tree manipulation functions End
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Nodes manipulation functions
/////////////////////////////////////////////////////////////////////////////////////////////////////

//isolates a node from the rest of the tree (its parent does not recongnise him 'poor child')
void	bTree::isolate()
{
	if (this->_parent)
	{
		if (this->_value < this->_parent->_value)
			this->_parent->_left = 0;
		else
			this->_parent->_right = 0;
	}
	else
		bTree::root = 0;
}

//node swaps position with 'this'
void	bTree::swap(bTree *node)
{
	bTree	*left;
	bTree	*right;
	bTree	*parent;

	parent = node->_parent;

	//parent swap
	this->replace(node);
	this->_parent = parent;
	if (parent)
	{
		if (node->_value < parent->_value)
			this->_parent->_left = this;
		else
			this->_parent->_right = this;
	}
	else
		bTree::root = this;
	
	//children swap
	left = node->_left;
	right = node->_right;
	node->_left = this->_left;
	node->_right = this->_right;
	this->_left = left;
	this->_right = right;
}

//node steals the parent of 'this' 
void	bTree::replace(bTree *node)
{
	node->_parent = this->_parent;
	if (this->_parent)
	{
		if (this->_value < this->_parent->_value)
			this->_parent->_left = node;
		else
			this->_parent->_right = node;
	}
	else
		bTree::root = node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Nodes manipulation functions End
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Rotations
/////////////////////////////////////////////////////////////////////////////////////////////////////

void    bTree::llRotate()
{
	bTree   *subRoot;

	subRoot = this->_left;

	//replace the current node with the subRoot
	this->replace(subRoot);
	
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

void    bTree::rrRotate()
{
	bTree   *subRoot;

	subRoot = this->_right;

	//replace the current node with the subRoot
	this->replace(subRoot);
	
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

void    bTree::lrRotate()
{
	bTree   *subRoot;

	subRoot = this->_left->_right;

	//replace the current node with the subRoot
	this->replace(subRoot);
	
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

void    bTree::rlRotate()
{
	bTree   *subRoot;

	subRoot = this->_right->_left;

	//replace the current node with the subRoot
	this->replace(subRoot);
	
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
/// Statu quo helper functions (do not change the tree nodes disposition)
/////////////////////////////////////////////////////////////////////////////////////////////////////
void    bTree::updateCounts()
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

bTree   *bTree::getInOrderSuccessor() const
{
	bTree	*ret;

	//the smallest key that is larger than x

	ret = 0;
	//left most child of its right subtree
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

bTree   *bTree::getInOrderPredeccessor() const
{
	bTree	*ret;

	//the largest key that is smaller than x

	ret = 0;
	//right most child of its left subtree
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

int   bTree::getBalanceFactor() const
{
	return this->_leftHeight - this->_rightHeight;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Statu quo helper functions End
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Getters End
/////////////////////////////////////////////////////////////////////////////////////////////////////

int   bTree::getValue() const
{
	return this->_value;
}

int   bTree::getLeftHeight() const
{
	return this->_leftHeight;
}
int   bTree::getRightHeight() const
{
	return this->_rightHeight;
}

bTree *bTree::getLeft() const
{
	return this->_left;
}

bTree *bTree::getRight() const
{
	return this->_right;
}

bTree *bTree::getParent() const
{
	return this->_parent;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Getters End
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Setters
/////////////////////////////////////////////////////////////////////////////////////////////////////

void    bTree::setValue(int value)
{
	this->_value = value;
}
void    bTree::setLeftHeight(int leftHeight)
{
	this->_leftHeight = leftHeight;
}

void    bTree::setRightHeight(int rightHeight)
{
	this->_rightHeight = rightHeight;
}

void    bTree::setLeft(bTree *left)
{
	this->_left = left;
}

void    bTree::setRight(bTree *right)
{
	this->_right = right;
}

void    bTree::setParent(bTree *parent)
{
	this->_parent = parent;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Setters End
/////////////////////////////////////////////////////////////////////////////////////////////////////


std::ostream &operator<<(std::ostream& ostr, bTree& root)
{
	ostr << "======================================================================================================================" << std::endl;
	printTree(ostr, &root, nullptr, false);
	ostr << "======================================================================================================================" << std::endl;
	return ostr;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
/// External
/////////////////////////////////////////////////////////////////////////////////////////////////////
void showTrunks(std::ostream& ostr, Trunk *p)
{
	if (p == nullptr) {
		return;
	}
 
	showTrunks(ostr, p->prev);
	ostr << p->str;
}
 
void printTree(std::ostream& ostr, bTree* root, Trunk *prev, bool isLeft)
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
	// ostr << " (" << root->getValue() << ")" << std::endl;
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