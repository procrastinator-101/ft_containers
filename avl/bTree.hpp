#ifndef BTREE_HPP
# define BTREE_HPP

#include <iostream>
#include <ostream>

#define COUNT 10

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

        void    insert(bTree& node);
        void    erase(bTree& node);

        void    setValue(int value);
        void    setLeft(bTree *left);
        void    setRight(bTree *right);
        void    setParent(bTree *parent);

        bTree *getLeft() const;
        bTree *getRight() const;
        bTree *getParent() const;
        const int   getValue() const;
};


std::ostream &operator<<(std::ostream& ostr, const bTree& root);
void print2DUtil(std::ostream& ostr, const bTree *root, int space);

#endif