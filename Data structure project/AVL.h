#include <iostream>
#include <fstream>
#include <cstdio>
#include "String.h"
using namespace std;

//const char* stringToCstring(String &s)
//{
//	int size = s.getLength();
//
//	char* cstr = new char[size + 1];
//	for (int i = 0;i < size;i++)
//	{
//		cstr[i] = s[i];
//	}
//
//	cstr[size] = '\0';
//
//	return cstr;
//}
void replaceLine(String filename, int l, String replace)
{
	ifstream file(filename.getdata());
	String arr[4];
	char* buffer = new char[1000];
	for (int i = 0;i < 4;i++)
	{
		file.getline(buffer, 1000);
		if (i == l - 1)
		{
			arr[i] = replace;
		}
		else
		{
			arr[i] = buffer;
		}
	}
	file.close();

	ofstream updated_file(filename.getdata());

	for (int i = 0;i < 4;i++)
	{
		updated_file << arr[i] << '\n';
	}
	updated_file.close();
	return;
}

char* getLineFile(String filename, int l)
{
	ifstream file(filename.getdata());
	char* buffer = new char[1000];
	for (int i = 0;i < l;i++)
	{
		file.getline(buffer, 1000);
	}
	return buffer;
}
int stringToInt(String& s) {
	int result = 0;
	int index = 0;

	int length = s.getLength();

	for (int i = index; i < length; i++) {
		result = result * 10 + (s[i] - '0');
	}

	return result;
}

char* extract(String s, int col, char end)
{
	int curr = 1;
	int count = 0;
	int length = s.getLength();
	//*temp = s;
	int i = 0;
	for (;length;i++)
	{
		if (curr > col)
		{
			break;
		}
		if (s[i] == end)
		{
			curr++;
			continue;
		}
		if (curr == col)
		{
			count++;

		}






	}

	char* result = new char[count + 1];
	int j = i - count - 1;
	int k = 0;
	for (;k < count;j++)
	{
		result[k++] = s[j];

	}
	result[count] = '\0';
	return result;
}
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
	String root;

	AVL_tree(String r = "nullptr") :root(r) {}

	void deletion(String& parent, int pos, String& rt);
	int height(String r)
	{
		if (r == "nullptr")
		{
			return -1;
		}

		String left(getLineFile(r, 2));
		String right(getLineFile(r, 3));
		int lt = height(left);
		int rt = height(right);
		return max(lt, rt) + 1;
	}
	void leftRotate(String& r)
	{
		String parent(getLineFile(r, 4));//store parent of current root
		String k(getLineFile(r, 3));//right child of root
		replaceLine(r, 3, getLineFile(k, 2));//roots right is k's left
		//r->right = k->left;
		replaceLine(k, 2, r);//ks left is r
		replaceLine(r, 4, k);//rs parent is k
		//k->left = r;
		//replace the root
		if (parent == "nullptr")
		{
			//if rotation occurs at trees root
			this->root = k;
			replaceLine(k, 4, parent);
		}
		else
		{
			replaceLine(parent, 3, k);
			replaceLine(k, 4, parent);//k s parent is roots parent initially
		}

	}

	void rightRotate(String& r)
	{
		/*AVL_node<t>* k = r->left;
		r->left = k->right;
		k->right = r;
		r = k;*/

		String parent(getLineFile(r, 4));//store parent of current root
		String k(getLineFile(r, 2));//leftt child of root
		replaceLine(r, 2, getLineFile(k, 3));//roots left is k's right

		replaceLine(k, 3, r);//ks right is r
		replaceLine(r, 4, k);//rs parent is k

		//replace the root
		if (parent == "nullptr")
		{
			//if rotation occurs at trees root
			this->root = k;
			replaceLine(k, 4, parent);
		}
		else
		{
			replaceLine(parent, 2, k);
			replaceLine(k, 4, parent);//k s parent is roots parent initially

		}
	}


	void insert(String val, String r, int col)
	{
		if (r == "nullptr")
		{
			String temp(extract(val, col, ';'));
			temp = temp + ".txt";
			this->root = temp;
			ofstream root(temp.getdata());
			temp = temp - ".txt";
			temp = temp + "_data.txt";
			ofstream dataFile(temp.getdata());
			root << temp << '\n';
			root << "nullptr" << '\n';//left child
			root << "nullptr" << '\n';//right child
			root << "nullptr" << '\n';//parent pointer

			dataFile << val << '\n';

		}
		else {
			ifstream root_node(r.getdata());
			if (!root_node.is_open()) {
				std::cerr << "Failed to open file: " << r.getdata() << '\n';
				return;
			}
			String new_val(extract(val, col, ';'));
			int new_intVal;
			int root_val;
			//we need to check wether to treat value as integer or charachter
			int i = 0;
			for (;i < new_val.getLength();i++)
			{
				if (new_val[i] < '0' || new_val[i]>'9')
				{
					break;
				}
			}
			//if col is integer eg we base on id
			if (i < new_val.getLength() && i>0)
			{
				new_intVal = stringToInt(new_val);
				String temp_root = r;
				temp_root = temp_root - ".txt";
				root_val = stringToInt(temp_root);
			}
			else//if col is string
			{
				//if less then we go to the left;
				if (new_val < r - ".txt")
				{
					char* buffer = new char[1000];
					root_node.getline(buffer, 1000, '\n');


					root_node.getline(buffer, 1000, '\n');

					String left(buffer);
					if (left == "nullptr")
					{
						//if it is null we need to create the node
						new_val = new_val + ".txt";
						ofstream new_node(new_val.getdata());
						String new_dataVal = new_val - ".txt";
						new_dataVal = new_dataVal + "_data" + ".txt";
						ofstream new_dataNode(new_dataVal.getdata());
						new_node << new_dataVal << '\n';
						new_node << "nullptr" << '\n';
						new_node << "nullptr" << '\n';
						new_node << r.getdata() << '\n';

						new_dataNode << val << '\n';
						//also need to update child pointer of parent node
						root_node.close();
						new_node.close();
						new_dataNode.close();
						replaceLine(r, 2, new_val);





					}
					else//if not null we recurse to that child
					{
						insert(val, left, col);

					}
					//after insertion we check if there is imbalance
					if (height(getLineFile(r, 3)) - height(getLineFile(r, 2)) == -2)
					{
						String left_child(getLineFile(r, 2));

						//single rotaion case
						if (height(getLineFile(left_child, 3)) - height(getLineFile(left_child, 2)) < 0)
						{
							rightRotate(r);
						}
						//double rotation case
						else
						{
							leftRotate(r);
							rightRotate(r);
						}
					}



				}



				//if greater then we go to the right;
				else if (new_val > (r - ".txt"))
				{
					char* buffer = new char[1000];
					root_node.getline(buffer, 1000, '\n');
					root_node.getline(buffer, 1000, '\n');


					root_node.getline(buffer, 1000, '\n');

					String right(buffer);
					if (right == "nullptr")
					{
						//if it is null we need to create the node
						new_val = new_val + ".txt";

						ofstream new_node(new_val.getdata());
						String new_dataVal = new_val - ".txt";
						new_dataVal = new_dataVal + "_data" + ".txt";
						ofstream new_dataNode(new_dataVal.getdata());

						new_node << new_dataVal << '\n';
						new_node << "nullptr" << '\n';
						new_node << "nullptr" << '\n';
						new_node << r.getdata() << '\n';



						new_dataNode << val << '\n';

						//also need to update child pointer of parent node
						root_node.close();
						new_node.close();
						new_dataNode.close();
						replaceLine(r, 3, new_val);





					}
					else//if not null we recurse to that child
					{
						insert(val, right, col);

					}
					//after insertion we check if there is imbalance
					if (height(getLineFile(r, 3)) - height(getLineFile(r, 2)) == 2)
					{
						String right_child(getLineFile(r, 3));

						//single rotaion case
						if (height(getLineFile(right_child, 3)) - height(getLineFile(right_child, 2)) > 0)
						{
							leftRotate(r);
						}
						//double rotation case
						else
						{
							rightRotate(r);
							leftRotate(r);
						}
					}

				}
				else//equal case
				{
					ofstream datafile(getLineFile(r, 1), std::ios::app);
					datafile << val << '\n';

				}


			}


		}
	}
	//default function for inserton ie if root parameter is nor passed it will use the root defined in the class
	void insert(String val)
	{
		insert(val, this->root);
	}

	String search_node(String val, String r)
	{
		if (r == "nullptr")
		{
			String null("nullptr");
			return null;
		}
		else if (val < r - ".txt")
		{
			//if value to be searched is less than root we search for it in the left subtree
			String left(getLineFile(r, 2));
			return search_node(val, left);
		}
		else if (val > r - ".txt")
		{
			//if value to be searched is less than root we search for it in the left subtree
			String right(getLineFile(r, 3));
			return search_node(val, right);
		}
		else
		{
			//this is the case if the value is found 
			//ie val==r->data

			return r;
		}
	}

	//default function for searching ie if root parameter is nor passed it will use the root defined in the class
	String search(t val)
	{
		return search(val, this->root);
	}


	void delete_node(String val, String& r)
	{
		if (r == "nullptr")
		{
			return;
		}
		else if (val < r - ".txt")
		{
			String left(getLineFile(r, 2));
			String right(getLineFile(r, 3));
			String lt = left - ".txt";
			String rt = right - ".txt";
			//conditions to determine wehter we need to replace the left or right of th parent node of the child to be deleeted
			if (lt == val)
			{
				deletion(r, 2, left);
			}
			else if (rt == val)
			{
				deletion(r, 3, right);
			}
			else
			{
				delete_node(val, left);
			}
		}
		else if (val > r - ".txt")
		{
			String left(getLineFile(r, 2));
			String right(getLineFile(r, 3));
			String lt = left - ".txt";
			String rt = right - ".txt";
			//conditions to determine wehter we need to replace the left or right of th parent node of the child to be deleeted
			if (val == lt)
			{
				deletion(r, 2, left);
			}
			else if (val == rt)
			{
				deletion(r, 3, right);
			}
			else
			{
				delete_node(val, right);
			}
			//after deletion we check if the balance is out

		}
		if (height(getLineFile(r, 3)) - height(getLineFile(r, 2)) == -2)
		{
			String left_child(getLineFile(r, 2));

			//single rotaion case
			if (height(getLineFile(left_child, 3)) - height(getLineFile(left_child, 2)) < 0)
			{
				rightRotate(r);
			}
			//double rotation case
			else
			{
				leftRotate(r);
				rightRotate(r);
			}
		}

		if (height(getLineFile(r, 3)) - height(getLineFile(r, 2)) == 2)
		{
			String right_child(getLineFile(r, 3));

			//single rotaion case
			if (height(getLineFile(right_child, 3)) - height(getLineFile(right_child, 2)) > 0)
			{
				leftRotate(r);
			}
			//double rotation case
			else
			{
				rightRotate(r);
				leftRotate(r);
			}
		}
		return;
	}


	////default function for deletion ie if root parameter is nor passed it will use the root defined in the class
	void delete_node(String val)
	{
		delete_node(val, this->root);
	}
	////default function for inorder traversal
	//void inorder()
	//{
	//	//if node is not passed then default value is root node
	//	inorder(this->root);
	//}
	//void inorder(AVL_node<t>* r)
	//{
	//	if (r == nullptr)
	//	{
	//		return;
	//	}
	//	inorder(r->left);7
	//	//cout << r->data << " ";
	//	inorder(r->right);

	//	return;

	//}

};

void AVL_tree<String>::deletion(String& parent, int pos, String& rt)//pos is either replace right or left child
{
	String left(getLineFile(rt, 2));
	String right(getLineFile(rt, 3));

	//only left child or no child case
	if (right == "nullptr")
	{
		replaceLine(parent, pos, left);
		if (!(left == "nullptr"))
		{
			replaceLine(left, 4, parent);
		}
		std::remove(rt.getdataCstr());
	}
	else if (left == "nullptr")//only right child case
	{
		replaceLine(parent, pos, right);
		if (!(right == "nullptr"))
		{
			replaceLine(right, 4, parent);
		}
		std::remove(rt.getdataCstr());
	}
	else
	{
		//both child case

		//we find the successor ie node to replace the current node 
		String succ(getLineFile(rt, 3));
		String dummy(getLineFile(succ, 2));
		while (dummy != "nullptr")
		{
			succ = dummy;
			dummy = (getLineFile(succ, 2));
		}

		//basically we will swap the nodes then delete

		//first we delelte the succesro node after saving it ie we change the parents left pointer to ncurrent node to be deletedull
		replaceLine(getLineFile(succ, 4), 2, rt);
		//then we we give the successors node the node to be deleteds children
		replaceLine(succ, 2, left);
		replaceLine(succ, 3, right);
		// we also change the childrens parent pointer to the successor
		replaceLine(left, 4, succ);
		replaceLine(right, 4, succ);

		//then we update the parent of node to be doleted to succ
		//and succ parent to the parent of deleted node
		replaceLine(succ, 4, parent);
		replaceLine(parent, pos, succ);

		//we also change the pointer of node to be deleted to null;
		replaceLine(rt, 2, "nullptr");
		replaceLine(rt, 3, "nullptr");
		replaceLine(rt, 4, getLineFile(succ, 4));

		String new_root(getLineFile(succ, 3));
		delete_node(rt - ".txt", new_root);
		//finally we remove the node
		//std::remove(r.getdataCstr());

	}
}