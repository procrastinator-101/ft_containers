#ifndef BTREE_HPP
# define BTREE_HPP

#include <iostream>
#include <ostream>


class bTree
{
	private:

		int     _value;
		int     _leftHeight;
		int     _rightHeight;

		bTree   *_left;
		bTree   *_right;
		bTree   *_parent;


		void	isolate();
		void	swap(bTree *node);
		void	replace(bTree *node);

		void    balance();

		void    llRotate();
		void    lrRotate();
		void    rlRotate();
		void    rrRotate();

		void    updateCounts();

		int     getBalanceFactor() const;
		bTree   *getInOrderSuccessor() const;
		bTree   *getInOrderPredeccessor() const;


	public:

		static bTree    *root;


		bTree();
		~bTree();

		bTree(int value);
		bTree(int value, bTree *left, bTree *right, bTree *parent);

		bTree(const bTree& src);
		bTree   &operator=(const bTree& rhs);

		void    erase(int value);
		void    insert(bTree& node);

		int   getValue() const;
		int   getLeftHeight() const;
		int   getRightHeight() const;

		bTree *getLeft() const;
		bTree *getRight() const;
		bTree *getParent() const;

		void    setValue(int value);
		void    setLeftHeight(int leftHeight);
		void    setRightHeight(int rightHeight);

		void    setLeft(bTree *left);
		void    setRight(bTree *right);
		void    setParent(bTree *parent);
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