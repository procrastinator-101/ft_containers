#include "testUtilities.hpp"
#include <vector>

namespace ft
{
  class TNode {
    public:
    int key;
    TNode *left;
    TNode *right;
    int height;
  };

  int max(int a, int b);

  // Calculate height
  int height(TNode *N) {
    if (N == NULL)
      return 0;
    return N->height;
  }

  int max(int a, int b) {
    return (a > b) ? a : b;
  }

  // New node creation
  TNode *newTNode(int key) {
    TNode *node = new TNode();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
  }

  // Rotate right
  TNode *rightRotate(TNode *y) {
    TNode *x = y->left;
    TNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
            height(y->right)) +
          1;
    x->height = max(height(x->left),
            height(x->right)) +
          1;
    return x;
  }

  // Rotate left
  TNode *leftRotate(TNode *x) {
    TNode *y = x->right;
    TNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
            height(x->right)) +
          1;
    y->height = max(height(y->left),
            height(y->right)) +
          1;
    return y;
  }

  // Get the balance factor of each node
  int getBalanceFactor(TNode *N) {
    if (N == NULL)
      return 0;
    return height(N->left) -
        height(N->right);
  }

  // Insert a node
  TNode *insertTNode(TNode *node, int key) {
    // Find the correct postion and insert the node
    if (node == NULL)
      return (newTNode(key));
    if (key < node->key)
      node->left = insertTNode(node->left, key);
    else if (key > node->key)
      node->right = insertTNode(node->right, key);
    else
      return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
                height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
      if (key < node->left->key) {
        return rightRotate(node);
      } else if (key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
      }
    }
    if (balanceFactor < -1) {
      if (key > node->right->key) {
        return leftRotate(node);
      } else if (key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
      }
    }
    return node;
  }

  // TNode with minimum value
  TNode *nodeWithMimumValue(TNode *node) {
    TNode *current = node;
    while (current->left != NULL)
      current = current->left;
    return current;
  }

  // Delete a node
  TNode *deleteTNode(TNode *root, int key) {
    // Find the node and delete it
    if (root == NULL)
      return root;
    if (key < root->key)
      root->left = deleteTNode(root->left, key);
    else if (key > root->key)
      root->right = deleteTNode(root->right, key);
    else {
      if ((root->left == NULL) ||
        (root->right == NULL)) {
        TNode *temp = root->left ? root->left : root->right;
        if (temp == NULL) {
          temp = root;
          root = NULL;
        } else
          *root = *temp;
        delete temp;
      } else {
        TNode *temp = nodeWithMimumValue(root->right);
        root->key = temp->key;
        root->right = deleteTNode(root->right,
                    temp->key);
      }
    }

    if (root == NULL)
      return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left),
                height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
      if (getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
      } else {
        root->left = leftRotate(root->left);
        return rightRotate(root);
      }
    }
    if (balanceFactor < -1) {
      if (getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
      } else {
        root->right = rightRotate(root->right);
        return leftRotate(root);
      }
    }
    return root;
  }

  void showTrunks(std::ostream& ostr, Trunk *p)
  {
    if (p == 0) {
      return;
    }
  
    showTrunks(ostr, p->prev);
    ostr << p->str;
  }
  void printTree(std::ostream& ostr, TNode* root, Trunk *prev, bool isLeft)
  {
    if (root == 0) {
      return;
    }
  
    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
  
    printTree(ostr, root->right, trunk, true);
  
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
    // ostr << " (" << root->getValue() << " | " << (root->getParent() ? root->getParent()->getValue() : -1) << ")" << std::endl;
    ostr << " " << root->key << std::endl;
    if (prev) {
      prev->str = prev_str;
    }
    trunk->str = "   |";
  
    printTree(ostr, root->left, trunk, false);
  }

  template<typename T, typename Compare, typename Alloc>
  bool	compareTrees(const typename ft::Avl<T, Compare, Alloc>::node_pointer a, const TNode *b)
  {
    bool	ret;

    if ((a && !b) || (b && !a))
      return false;
    if (!a && !b)
      return true;
    if (a->_value != b->key)
      return false;
    ret = compareTrees<T, Compare, Alloc>(a->_traits.left, b->left);
    if (ret == false)
      return ret;
    return compareTrees<T, Compare, Alloc>(a->_traits.right, b->right);
  }
}

void	testInsertDelete(std::vector<int>& numbers)
{
	int		idx;
	bool	ret;

	ft::TNode *root = NULL;
	ft::Avl<int, std::less<int>, std::allocator<int> >	a;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		a.insert(numbers[i]);
		root = insertTNode(root, numbers[i]);
		ret = ft::compareTrees<int, std::less<int>, std::allocator<int> >(a._root, root);
		if (ret == false)
		{
			a.show();
			printTree(std::cout, root, 0, false);
			std::cout << "insert : KO !!!!!!!!" << std::endl;
			return ;
		}
	}
	std::cout << "insert : OK" << std::endl;

	for (size_t i = 0; i < numbers.size(); i++)
	{
		idx = std::rand() % numbers.size();
		a.erase(numbers[idx]);
		root = deleteTNode(root, numbers[idx]);
		ret = ft::compareTrees<int, std::less<int>, std::allocator<int> >(a._root, root);
		if (ret == false)
		{
			a.show();
			printTree(std::cout, root, 0, false);
			std::cout << "delete : KO !!!!!!!!" << std::endl;
			return ;
		}
		numbers.erase(numbers.begin() + idx);
	}
	std::cout << "delete : OK" << std::endl;
}