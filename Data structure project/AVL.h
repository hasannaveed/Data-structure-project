#include <iostream>
using namespace std;

//avl node struct
template <typename t>
struct AVL_node {
	int key;
	t data;
	AVL_node* left;
	AVL_node* right;

	//constructor to initialise avl node
	
	AVL_node(t d = 0, AVL_node* l = nullptr, AVL_node* r = nullptr) :data(d), left(l), right(r)
	{

	}
};

template <typename t>
class AVL_tree {
public:
	AVL_node<t>* root;

	void insert(t val)
	{

	}

	void search(t val)
	{

	}

	void delete(t val)
	{

	}
	
};