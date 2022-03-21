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
    bTree   *subRoot;

    subRoot = this->_left;

    //replace the current node with the subRoot
    subRoot->setParent(this->_parent);
    if (this->_parent)
    {
        if (this->_value < this->_parent->getValue())
            this->_parent->setLeft(subRoot);
        else
            this->_parent->setRight(subRoot);
    }
    else
        bTree::root = subRoot;
    
    //make the current node the right child of the subRoot
        //let the right child of the subRoot embrace its left child
    this->_left = subRoot->getRight();
    if (this->_left)
        this->_left->setParent(this);
        //let the subroot welcome its right child
    this->_parent = subRoot;
    subRoot->setRight(this);

    //update the height of subRoot and its right child
    subRoot->getRight()->updateCounts();
    subRoot->updateCounts();
}

void    bTree::rrRotate()
{
    bTree   *subRoot;

    subRoot = this->_right;

    //replace the current node with the subRoot
    subRoot->setParent(this->_parent);
    if (this->_parent)
    {
        if (this->_value < this->_parent->getValue())
            this->_parent->setLeft(subRoot);
        else
            this->_parent->setRight(subRoot);
    }
    else
        bTree::root = subRoot;
    
    //make the current node the left child of the subRoot
        //let the left child of the subRoot embrace its right child
    this->_right = subRoot->getLeft();
    if (this->_right)
        this->_right->setParent(this);
        //let the subroot welcome its left child
    this->_parent = subRoot;
    subRoot->setLeft(this);
    
    //update the height of subRoot and its left child
    subRoot->getLeft()->updateCounts();
    subRoot->updateCounts();
}

void    bTree::lrRotate()
{
    bTree   *subRoot;

    subRoot = this->_left->getRight();

    //replace the current node with the subRoot
    subRoot->setParent(this->_parent);
    if (this->_parent)
    {
        if (this->_value < this->_parent->getValue())
            this->_parent->setLeft(subRoot);
        else
            this->_parent->setRight(subRoot);
    }
    else
        bTree::root = subRoot;
    
    //adjsut the left child of the subRoot
        //let the left child of the subroot embrace its new right child
    this->_left->setRight(subRoot->getLeft());
    if (subRoot->getLeft())
        subRoot->getLeft()->setParent(this->_left);
        //let the subroot welcome its left child
    subRoot->setLeft(this->_left);
    this->_left->setParent(subRoot);

    //adjust the right child of the subRoot
        //let the right child of the subroot embrace its new left child
    this->_left = subRoot->getRight();
    if (this->_left)
        this->_left->setParent(this);
        //let the subroot welcome its right child
    subRoot->setRight(this);
    this->_parent = subRoot;

    //update the height of subRoot and its childs
    subRoot->getLeft()->updateCounts();
    subRoot->getRight()->updateCounts();
    subRoot->updateCounts();
}

void    bTree::rlRotate()
{
    bTree   *subRoot;

    subRoot = this->_right->getLeft();

    //replace the current node with the subRoot
    subRoot->setParent(this->_parent);
    if (this->_parent)
    {
        if (this->_value < this->_parent->getValue())
            this->_parent->setLeft(subRoot);
        else
            this->_parent->setRight(subRoot);
    }
    else
        bTree::root = subRoot;
    
    //adjsut the right child of the subRoot
        //let the right child of the subroot embrace its new left child
    this->_right->setLeft(subRoot->getRight());
    if (subRoot->getRight())
        subRoot->getRight()->setParent(this->_right);
        //let the subroot welcome its right child
    subRoot->setRight(this->_right);
    this->_right->setParent(subRoot);

    //adjsut the left child of the subRoot
        //let the left child of the subroot embrace its new right child
    this->_right = subRoot->getLeft();
    if (this->_right)
        this->_right->setParent(this);
        //let the subroot welcome its left child
    subRoot->setLeft(this);
    this->_parent = subRoot;

    //update the height of subRoot and its childs
    subRoot->getLeft()->updateCounts();
    subRoot->getRight()->updateCounts();
    subRoot->updateCounts();
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
/// External
/////////////////////////////////////////////////////////////////////////////////////////////////////