#include <iostream>
#include "AVL.h"
#include "Btree.h"
using namespace std;


int main() {

	//testing the avl tree

	/*AVL_tree<int> tree;
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(8);
	tree.insert(9);
	tree.insert(10);
	tree.deletion(10);
	tree.deletion(6);
	tree.inorder();*/


	//testing the btree
	Btree<int> tree(3);
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(8);
	tree.insert(9);
	tree.insert(10);
	return 0;
}