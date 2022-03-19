#include "bTree.hpp"

#define COUNT 10

bTree::bTree() : _value(0), _left(0), _right(0), _parent(0)
{
}

bTree::~bTree()
{
}

bTree::bTree(int value, bTree *left, bTree *right, bTree *parent) : _value(value), _left(left), _right(right), _parent(parent)
{
}

bTree::bTree(const bTree& src) : _value(src.getValue()), _left(src.getLeft()), _right(src.getRight()), _parent(src.getParent())
{
}

bTree   &bTree::operator=(const bTree& rhs)
{
    this->_left = rhs.getLeft();
    this->_right = rhs.getRight();
    this->_parent = rhs.getParent();
    this->_value = rhs.getValue();
    return *this;
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
            this->_right = &node;
    }
    else
    {
        if (this->_left)
            this->_left->insert(node);
        else
            this->_left = &node;
    }
}

void    bTree::erase(bTree& node)
{
    if (this->_value == node.getValue())
    {
        if (this->_value < this->_parent->getValue())
            this->_parent->setLeft(0);
        else
            this->_parent->setRight(0);
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
}


void    bTree::setValue(int value)
{
    this->_value = value;
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

const int   bTree::getValue() const
{
    return this->_value;
}

void print2DUtil(std::ostream& ostr, const bTree *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(ostr, root->getRight(), space);
 
    // Print current node after space
    // count
    ostr << std::endl;
    for (int i = COUNT; i < space; i++)
        ostr << " ";
    ostr << root->getValue() << std::endl;
 
    // Process left child
    print2DUtil(ostr, root->getLeft(), space);
}

std::ostream &operator<<(std::ostream& ostr, const bTree& root)
{
    print2DUtil(ostr, &root, 0);
    return ostr;
}
