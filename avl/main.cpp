#include "bTree.hpp"

int main(int argc, char **argv)
{
    bTree   *root;
    bTree   *node;
    
    if (argc < 2)
        return 0;
    root = new bTree(std::atoi(argv[1]));
    for (int i = 2; i < argc; i++)
    {
        node = new bTree(std::atoi(argv[i]));
        root->insert(*node);
    }

    std::cout << (*root) << std::endl;

	root->erase(*node);
	delete node;

	std::cout << (*root) << std::endl;
    return 0;
}