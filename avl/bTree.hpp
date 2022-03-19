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


std::ostream &operator<<(std::ostream& ostr, bTree& root);
void printBT(std::ostream& ostr, const std::string& prefix, const bTree *node, bool isLeft);

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

#endif