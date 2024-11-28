#pragma once
#include <iostream>
using namespace std;

//btree node struct
template <typename t>
struct Btree_node {

	String fileName;
	int order			//order of the btree
	t*keys				//array of teh keys
	Btree_node*children //array to keep track of the child pointers

	
};