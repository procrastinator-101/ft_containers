#include "bTree.hpp"

bTree    *bTree::root = 0;

int main(int argc, char **argv)
{
    bTree   *node;
    
    if (argc < 2)
        return 0;
    bTree::root = new bTree(std::atoi(argv[1]));
    for (int i = 2; i < argc; i++)
    {
        node = new bTree(std::atoi(argv[i]));
        bTree::root->insert(*node);
    }

    std::cout << (*bTree::root) << std::endl;

	// root->erase(*node);
	// delete node;

	// std::cout << (*root) << std::endl;
    return 0;
}