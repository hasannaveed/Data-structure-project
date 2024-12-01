#pragma once
#include <iostream>
#include <cmath>//for ceil function
using namespace std;

//btree node struct
template <typename t>
struct Btree_node {

	int order;				//order of the btree
	t* keys;				//array of teh keys
	Btree_node** children;  //array to keep track of the child pointers
	int n;					//current number of keys

	bool leaf;

	Btree_node(int o = 0, t* k = nullptr, Btree_node** c = nullptr, int num = 0, bool l = true)
	{
		order = o;
		if (k == nullptr)
		{
			keys = new t[order];
		}
		else
		{
			keys = k;


		}
		if (c == nullptr)
		{
			children = new Btree_node * [order + 1];
			for (int i = 0;i < order;i++)
			{
				//initially we set all child pointers to null
				children[i] = nullptr;
			}
		}
		else
		{
			children = c;
		}
		n = num;
		leaf = l;
	}
};

template <typename t>
class Btree {
public:
	int order;
	int max_keys;		//variable to stor the maximum amount of keys so we can split when limit reached   ceil(m/2-1)----(m-1)
	int max_children;	//variable to stor the maximum amount of children so we can split when limit reached	ceil(m/2)---m
	Btree_node<t>* root;

	Btree(int o = 0, Btree_node<t>* r = nullptr)
	{
		order = o;
		max_keys = o - 1;
		max_children = o;
		root = r;
	}
	//function to sort the keys in incresing order
	void sort(t*& k, int n)
	{
		//bubble sort
		for (int i = 0;i < n - 1;i++)
		{
			for (int j = 0;j < n - 1;j++)
			{
				if (k[j] > k[j + 1])
				{
					int temp = k[i];
					k[i] = k[i + 1];
					k[i + 1] = temp;
				}
			}
		}
	}
	//function to split child in case num of keys exceeded
	void splitChild(Btree_node<t>*& parent, int i)
	{
		//we find the child node that needs to be split
		Btree_node<t>* childToSplit = parent->children[i];
		//we crete the new node 
		Btree_node<t>* new_node = new Btree_node<t>(order);
		new_node->leaf = childToSplit->leaf;

		if (order % 2 != 0)
		{


			//we adjust the count of keys on new node
			//we shift half of the keys to the new node
			new_node->n = ceil((order / 2.0)) - 1;
			for (int j = 0; j < int(ceil((order / 2.0))) - 1; j++)
				new_node->keys[j] = childToSplit->keys[j + int(ceil((order / 2.0)))];
			//we then move the child pointers also if it is not a leaf node
			if (!childToSplit->leaf) {
				for (int j = 0; j < ceil((order / 2.0)); j++)
					new_node->children[j] = childToSplit->children[j + int(ceil((order / 2.0)))];
			}
			childToSplit->n = ceil((order / 2.0)) - 1;

			//we adjust the child pointers of the parent node to accomodate the new node
			for (int j = parent->n; j >= i + 1; j--)
				parent->children[j + 1] = parent->children[j];
			parent->children[i + 1] = new_node;

			//promote the middle node to the parent
			for (int j = parent->n - 1; j >= i; j--)
				parent->keys[j + 1] = parent->keys[j];
			parent->keys[i] = childToSplit->keys[int(ceil(order / 2.0)) - 1];

			//update parent key count
			parent->n = parent->n + 1;
		}
		else
		{
			new_node->n = order / 2;
			for (int j = 0; j < order / 2; j++)
				new_node->keys[j] = childToSplit->keys[j + order / 2];
			//we then move the child pointers also if it is not a leaf node
			if (!childToSplit->leaf) {
				for (int j = 0; j < order / 2.0; j++)
					new_node->children[j] = childToSplit->children[j + order / 2];
			}
			childToSplit->n = order / 2 - 1;

			//we adjust the child pointers of the parent node to accomodate the new node
			for (int j = parent->n; j >= i + 1; j--)
				parent->children[j + 1] = parent->children[j];
			parent->children[i + 1] = new_node;

			//promote the middle node to the parent
			for (int j = parent->n - 1; j >= i; j--)
				parent->keys[j + 1] = parent->keys[j];
			parent->keys[i] = childToSplit->keys[(order / 2) - 1];

			//update parent key count
			parent->n = parent->n + 1;
		}
	}
	void insertNonFull(t val, Btree_node<t>*& r)
	{

		//if root is empty we just simply insert at first position
		/*if (r == nullptr)
		{
			r = new Btree_node(order);
			r->keys[0] = val;
			r->n++;
		}*/
		//else
		{
			if (r->leaf)
			{
				//we only insert in leaf node 
				//if node is not leaf we need to recurse to leaf node

					//if there is space we insert the value and then sort it
				r->keys[r->n] = val;
				r->n++;
				sort(r->keys, r->n);



			}
			else
			{
				//we iterate through the keys array to find which child we should go to
				//as soon as we find the key which is greter than our value we know that our value should lie in the child before that key
				int i = 0;
				for (;i < r->n;i++)
				{
					if (val < r->keys[i])
					{
						break;
					}
				}
				//if child to be recursed to is full we need to split the child

				insertNonFull(val, r->children[i]);//we recurse to that child
				if (r->children[i]->n == max_keys + 1)
				{
					splitChild(r, i);
					if (val > r->keys[i])
						i++;
				}

			}
		}
	}
	void insert(t val)
	{
		insert(val, this->root);
	}
	void insert(t val, Btree_node<t>*& r)
	{
		if (r == nullptr)
		{
			r = new Btree_node<t>(order);
			r->leaf = true;
			r->keys[0] = val;
			r->n = 1;

			return;
		}
		if (r->leaf && r->n == max_keys) {
			Btree_node<t>* new_root = new Btree_node<t>(this->order);
			new_root->leaf = false;
			new_root->children[0] = r;
			r = new_root;
			insertNonFull(val, new_root->children[0]);
			splitChild(new_root, 0);
		}
		else
		{
			insertNonFull(val, r);
			//if root node has more than  max keys we need to split the node
			if (r->n == max_keys + 1)
			{
				Btree_node<t>* new_root = new Btree_node<t>(this->order);
				new_root->leaf = false;
				new_root->children[0] = r;
				r = new_root;

				splitChild(new_root, 0);
			}
		}

	}

};
