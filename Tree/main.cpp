#include "tree.h"

#include <iostream>

int main()
{
	Tree::Tree<int> tree;
	int a = 7;
	int b = 13;
	int c = 3;
	int d = 1;
	int e = 9;
	int f = 5;

	std::cout << "a = 0x" << &a << std::endl;
	std::cout << "b = 0x" << &b << std::endl;
	std::cout << "c = 0x" << &c << std::endl;
	std::cout << "d = 0x" << &d << std::endl;
	std::cout << "e = 0x" << &e << std::endl;
	std::cout << "f = 0x" << &f << std::endl;

	std::cout << std::endl;

	tree.add_node(nullptr, &a);
	tree.add_node(nullptr, &c);
	tree.add_node(&c, &d);
	tree.add_node(&c, &e);
	tree.add_node(&e, &f);
	tree.add_node(nullptr, &b);

	tree.print_tree();

	std::cin.get();

	return 0;
}