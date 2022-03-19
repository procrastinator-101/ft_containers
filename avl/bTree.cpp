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

std::ostream &operator<<(std::ostream& ostr, bTree& root)
{
	// printBT(ostr, "", &root, false);
	printTree(ostr, &root, nullptr, false);
	return ostr;
}

void printBT(std::ostream& ostr, const std::string& prefix, const bTree *node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        ostr << node->getValue() << std::endl;

        // enter the next tree level - left and right branch
        printBT(ostr, prefix + (isLeft ? "│   " : "    "), node->getLeft(), true);
        printBT(ostr, prefix + (isLeft ? "│   " : "    "), node->getRight(), false);
    }
}

 
// Helper function to print branches of the binary tree
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