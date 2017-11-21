#ifndef BPTREE_H
#define BPTREE_H

#include <BPTreeNode.h>

using namespace std;

/**
	class definition for B+ Tree
*/
class BPTree{
	int order;
	BPTreeNode* root;	/** reference to this B+ tree, all queries are run through this node, initially empty */

	public:
		BPTree(int);
		
		void insert(double, string);
		string search(double);
		string rangeSearch(double, double);
		string vec2string(vector<string>&);
};

#endif
