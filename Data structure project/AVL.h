#include <iostream>
using namespace std;

//avl node struct
template <typename t>
struct AVL_node {
	t data;
	AVL_node* left;
	AVL_node* right;

	//constructor to initialise avl node
	
	AVL_node(t d = 0, AVL_node* l = nullptr, AVL_node<t>* r = nullptr) :data(d), left(l), right(r)
	{

	}
};

template <typename t>
class AVL_tree {
public:
	AVL_node<t>* root;

	AVL_tree(AVL_node<t>* r = nullptr) :root(r) {}

	int height(AVL_node<t>* r)
	{
		if (r == nullptr)
		{
			return -1;
		}

		int lt = height(r->left);
		int rt = height(r->right);
		return max(lt,rt)+1;
	}
	void leftRotate(AVL_node<t>*& r)
	{
		AVL_node<t>* k = r->right;
		r->right = k->left;
		k->left = r;
		r = k;
	}
	
	void rightRotate(AVL_node<t>*& r)
	{
		AVL_node<t>* k = r->left;
		r->left = k->right;
		k->right = r;
		r = k;
	}
	
	void insert(t val,AVL_node<t>*&r)
	{
		if (r == nullptr)
		{
			r = new AVL_node<t>(val);
		}
		else if (val < r->data)  //if the value to be inserted is less than teh root we insert at the left
		{
			insert(val, r->left);

			//after insertion we check the balance factor
			if (height(r->right) - height(r->left) == -2)
			{
				//if tree is unbalanced we also need to chek the bf of subtree
				//in order to know if we need to rotate once or twice

				if (height(r->left->right) - height(r->left->left) == -1)
				{
					//case of single rotation
					rightRotate(r);
				}
				else
				{
					//case of double rotation
					leftRotate(r->left);
					rightRotate(r);
				}
			}
		}
		else		//if value to be inserted iis larger than the root we insert to the right
		{
			insert(val, r->right);


			//after insertion we check the balance factor
			if (height(r->right) - height(r->left) == 2)
			{
				//if tree is unbalanced we also need to chek the bf of subtree
				//in order to know if we need to rotate once or twice

				if (height(r->right->right) - height(r->right->left) == 1)
				{
					//case of single rotation
					leftRotate(r);
				}
				else
				{
					//case of double rotation
					rightRotate(r->right);
					leftRotate(r);
				}
			}
		}
	}
	//default function for inserton ie if root parameter is nor passed it will use the root defined in the class
	void insert(t val)
	{
		insert(val, this->root);
	}

	AVL_node<t>* search(t val,AVL_node<t>*r)
	{
		if (r == nullptr)
		{
			return nullptr;
		}
		else if (val < r->data)
		{
			//if value to be searched is less than root we search for it in the left subtree
			return search(val, r->left);
		}
		else if (val > r->data)
		{
			//if value to be searched is gretaer than root we search for it in the right subtree
			return search(val, r->right);
		}
		else
		{
			//this is the case if the value is found 
			//ie val==r->data

			return r->data;
		}
	}

	//default function for searching ie if root parameter is nor passed it will use the root defined in the class
	AVL_node<t>* search(t val)
	{
		return search(val, this->root);
	}
	
	void deletion(t val,AVL_node<t>* &r)
	{
		if (r == nullptr)
		{
			return;
		}
		else if (val < r->data)
		{
			deletion(val, r->left);
		}
		else if (val > r->data)
		{
			deletion(val, r->right);

		}
		else
		{
			///value is found
			AVL_node<t>* temp;
			///if leaf node or one child left node
			if (r->right == nullptr)
			{
				temp = r;
				r = r->left;
				delete temp;
			}
			//only right child case
			else if (r->left == nullptr)
			{
				temp = r;
				r = r->right;
				delete temp;
			}
			else  //both child case
			{
				//we find the successor to replace the current node
				AVL_node<t>* curr = r->right;
				while (curr->left)
				{
					curr = curr->left;
				}
				r->data = curr->data;

				deletion(curr->data, curr);
			}

			/////////////////////////////////////////////////////////////////
			// after deletion we need to check if the node is stil balanced//
			/////////////////////////////////////////////////////////////////

			if (r == nullptr)
			{
				return;
			}

			//if tree is right heavy
			if (height(r->right) - height(r -> left) > 1)
			{
				if (height(r->right) - height(r -> left) >= 0)
				{
					//single rotatioj case
					leftRotate(r);
				}
				else
				{
					//double rotation case
					rightRotate(r->right);
					leftRotate(r);
				}
			}
			//if tree is left heavy
			if (height(r->right) - height(r -> left) < -1) 
			{
				if (height(r->right) - height(r -> left) <= 0)
				{
					//single rotation case
					rightRotate(r);
				}
				else
				{
					//double rotation case
					leftRotate(r->left);
					rightRotate(r);
				}
			}
		}
	}
	//default function for deletion ie if root parameter is nor passed it will use the root defined in the class
	void deletion(t val)
	{
		deletion(val, this->root);
	}
	//default function for inorder traversal
	void inorder()
	{
		//if node is not passed then default value is root node
		inorder(this->root);
	}
	void inorder(AVL_node<t>*r)
	{
		if (r == nullptr)
		{
			return;
		}
		inorder(r->left);
		cout << r->data << " ";
		inorder(r->right);

		return;

	}
	
};