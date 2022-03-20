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

bTree::bTree(const bTree& src) : _value(src.getValue()), _leftHeight(src.getLeftHeight()), _rightHeight(src.getRightHeight()), _left(src.getLeft()), _right(src.getRight()), _parent(src.getParent())
{
}

bTree::bTree(int value) : _value(value), _leftHeight(0), _rightHeight(0), _left(0), _right(0), _parent(0)
{
}

bTree   &bTree::operator=(const bTree& rhs)
{
    this->_value = rhs.getValue();
    this->_leftHeight = rhs.getLeftHeight();
    this->_rightHeight = rhs.getRightHeight();

    this->_left = rhs.getLeft();
    this->_right = rhs.getRight();
    this->_parent = rhs.getParent();
    return *this;
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
        subBalanceFactor = this->_left->getBalanceFactor();
        if (subBalanceFactor < 0)
            this->llRotate();
        else
            this->lrRotate();
    }
    else
    {
        subBalanceFactor = this->_right->getBalanceFactor();
        if (subBalanceFactor < 0)
            this->rlRotate();
        else
            this->rrRotate();
    }
}

void    bTree::insert(bTree& node)
{
    if (this->_value == node.getValue())
        return;
    else if (this->_value < node.getValue())
    {
        if (this->_right)
            this->_right->insert(node);
        else
        {
            this->_right = &node;
            node.setParent(this);
        }
    }
    else
    {
        if (this->_left)
            this->_left->insert(node);
        else
        {
            this->_left = &node;
            node.setParent(this);
        }
    }
    this->updateCounts();
    this->balance();
}

void    bTree::erase(bTree& node)
{
    if (this->_value == node.getValue())
    {
        if (this->_parent)
        {
            if (this->_value < this->_parent->getValue())
                this->_parent->setLeft(0);
            else
                this->_parent->setRight(0);
        }
    }
    else if (this->_value < node.getValue())
    {
        if (this->_right)
            this->_right->erase(node);
    }
    else
    {
        if (this->_left)
            this->_left->erase(node);
    }
    this->updateCounts();
}

void    bTree::llRotate()
{
    bTree   *root;

    root = this->_left;
    //replace the current node with the root
    root->setParent(this->_parent);
    if (this->_value < this->_parent->getValue())
        this->_parent->setLeft(root);
    else
        this->_parent->setRight(root);
    //make the current node the right child of the root
    this->_parent = root;
    this->_left = root->getRight();
    root->setRight(this);
    //update the height of root and its right child
    root->getRight()->updateCounts();
    root->updateCounts();
}

void    bTree::rrRotate()
{
    bTree   *root;

    root = this->_right;
    //replace the current node with the root
    root->setParent(this->_parent);
    if (this->_value < this->_parent->getValue())
        this->_parent->setLeft(root);
    else
        this->_parent->setRight(root);
    //make the current node the left child of the root
    this->_parent = root;
    this->_right = root->getLeft();
    root->setLeft(this);
    //update the height of root and its left child
    root->getLeft()->updateCounts();
    root->updateCounts();
}

void    bTree::lrRotate()
{
    bTree   *root;

    root = this->_left->getRight();
    //replace the current node with the right child of its left child
    root->setParent(this->_parent);
    if (this->_value < this->_parent->getValue())
        this->_parent->setLeft(root);
    else
        this->_parent->setRight(root);
    //adjsut the left child of the root
    this->_left->setRight(root->getLeft());
    root->getLeft()->setParent(this->_left);
    root->setLeft(this->_left);
    this->_left->setParent(root);
    //adjust the right child of the root
    this->_left = root->getRight();
    this->_left->setParent(this);
    root->setRight(this);
    this->_parent = root;
    //update the height of root and its childs
    root->getLeft()->updateCounts();
    root->getRight()->updateCounts();
    root->updateCounts();
}

void    bTree::rlRotate()
{
    bTree   *root;

    root = this->_right->getLeft();
    //replace the current node with the right child of its left child
    root->setParent(this->_parent);
    if (this->_value < this->_parent->getValue())
        this->_parent->setLeft(root);
    else
        this->_parent->setRight(root);
    //adjsut the right child of the root
    this->_right->setLeft(root->getRight());
    root->getRight()->setParent(this->_right);
    root->setRight(this->_right);
    this->_right->setParent(root);
    //adjsut the left child of the root
    this->_right = root->getLeft();
    this->_right->setParent(this);
    root->setLeft(this);
    this->_parent = root;
    //update the height of root and its childs
    root->getLeft()->updateCounts();
    root->getRight()->updateCounts();
    root->updateCounts();
}

void    bTree::updateCounts()
{
    if (this->_left)
        this->_leftHeight = std::max(this->_left->getLeftHeight(), this->_left->getRightHeight()) + 1;
    else
        this->_leftHeight = 0;
    if (this->_right)
        this->_rightHeight = std::max(this->_right->getLeftHeight(), this->_right->getRightHeight()) + 1;
    else
        this->_rightHeight = 0;
}

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
int   bTree::getBalanceFactor() const
{
    return this->_leftHeight - this->_rightHeight;
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


std::ostream &operator<<(std::ostream& ostr, bTree& root)
{
	printTree(ostr, &root, nullptr, false);
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
    ostr << " " << root->getValue() << std::endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(ostr, root->getLeft(), trunk, false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// External
/////////////////////////////////////////////////////////////////////////////////////////////////////