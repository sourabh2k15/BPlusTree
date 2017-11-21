#include <BPTree.h>

/** 
 	constructor creates and initializes a B+ tree with given order
    all queries are run on the root node pointer, which is updated in inserts if necessary ( nodes split root could change)
 */
BPTree::BPTree(int m){
	order = m;
	root = new BPTreeNode(m, true);
}

/**
	Insert procedure for the B+ tree. (double, string) expected as key, value. 
*/
void BPTree::insert(double key, string val){
	stack<BPTreeNode*> path;
	root->insert(key, val, path, root);
}

/**	
	Retrieves string value for a given if it exists in the B+ tree or returns "Null"
*/
string BPTree::search(double key){
	vector<string> result;
	root->search(key, result);
	
	string output = vec2string(result);
	return output;
}

/**
	Conducts range search for the given closed range [key1, key2] (double, double)
*/
string BPTree::rangeSearch(double key1, double key2){
	vector<string> result;
	root->rangeSearch(key1, key2, result);

	string output = vec2string(result);
	return output;
}

/** 
	Utility method, converts vector to a formatted string
*/
string BPTree::vec2string(vector<string>& result){
	string s;

	for(int i = 0; i < (int)result.size()-1; i++){
		s += result[i] + ",";
	}
	
	s += result[result.size()-1];
	return s;
}
