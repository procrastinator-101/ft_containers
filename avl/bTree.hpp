#ifndef BTREE_HPP
# define BTREE_HPP

#include <iostream>
#include <ostream>


class bTree
{
    private:
        int     _value;
        bTree   *_left;
        bTree   *_right;
        bTree   *_parent;


    public:
        bTree();
        ~bTree();
        bTree(int value, bTree *left, bTree *right, bTree *parent);
        bTree(const bTree& src);
        bTree   &operator=(const bTree& rhs);

        void    erase(bTree& node);
        void    insert(bTree& node);


        void    llRotate();
        void    lrRotate();
        void    rlRotate();
        void    rrRotate();

        void    setValue(int value);
        void    setLeft(bTree *left);
        void    setRight(bTree *right);
        void    setParent(bTree *parent);

        int   getValue() const;
        bTree *getLeft() const;
        bTree *getRight() const;
        bTree *getParent() const;
};


std::ostream &operator<<(std::ostream& ostr, bTree& root);

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

void printTree(std::ostream& ostr, bTree* root, Trunk *prev, bool isLeft);

/////////////////////////////////////////////////////////////////////////////////////////////////////
/// External
/////////////////////////////////////////////////////////////////////////////////////////////////////

#endif