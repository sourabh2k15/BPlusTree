#include <BPTreeNode.h>
#include <BPTreeNodeElement.h>

/**
	Class defining the individual nods of the B+ tree. Each of these nodes has an array of key objects ( BPTreeNodeElement )
 */
BPTreeNode::BPTreeNode(int t_m, bool t_isLeaf){
	isLeaf = t_isLeaf;							/** true if it is a leaf node or false otherwise */
	order = t_m;								/** order of the B+ tree*/
	filled = 0;									/** determines how much of the array of key objects is filled */
	keyNodes = new BPTreeNodeElement[order+1];	/** array of key objects of length (order + 1) */
	next = nullptr;
	prev = nullptr;
}

/**
	Alternate constructor to initialize Node when splitting occurs. This constructor allows us to predefine the key values 
*/
BPTreeNode::BPTreeNode(int t_m, bool t_isLeaf, BPTreeNodeElement* t_keyNodes){
	keyNodes = t_keyNodes;
	order = t_m;
	filled = 0;	
	isLeaf = t_isLeaf;	
}

/** Setter for next pointer. Useful only in leaf nodes (maintaining a doubly linked list) */
void BPTreeNode::setNext(BPTreeNode* t_next){
	next = t_next;
}

/** Getter for next pointer. */
BPTreeNode* BPTreeNode::getNext(){
	return next;
}

/** Setter for previous pointer. Useful only for leaf nodes */
void BPTreeNode::setPrev(BPTreeNode* t_prev){
	prev = t_prev;
}

/** Getter for previous pointer*/
BPTreeNode* BPTreeNode::getPrev(){
	return prev;
}

/** Setter to update / set how much of the keys array is filled */
void BPTreeNode::setFilled(int f){
	filled = f;
}

/** To determine if the node is overflowing and a split is needed */
bool BPTreeNode::isOverflow(){
	return filled == order+1; 
}

/** Insert procedure to recursively insert bottom up when a node splits */
void BPTreeNode::insert(BPTreeNodeElement* keyElement, stack<BPTreeNode*>& path, BPTreeNode*& root){
	int pos = 0;
		
	for(; pos < filled; pos++){
		if(keyNodes[pos].getKey() > keyElement->getKey()) break;
	}
	
	for(int j = filled; j > pos; j--){
		keyNodes[j] = keyNodes[j-1];
	}
	
	keyNodes[pos] = *keyElement;
	if(pos+1 < filled){ 
		keyNodes[pos+1].setLeft(keyNodes[pos].getRight());
	}
	filled++;
	
	if(isOverflow()) splitNode(path, root);	
}

/** 
	Insert procedure to search for leaf top down and insert (double, string) key value.
	The root to leaf nodes are stored in a stack and are used for bottom up recursive insert if needed after node spits
  */
void BPTreeNode::insert(double key, string val, stack<BPTreeNode*>& path, BPTreeNode*& root){
	if(isLeaf){
		int pos = 0;
		
		for(; pos < filled; pos++){
			if(keyNodes[pos].getKey() >= key) break;
		}
			
		if(keyNodes[pos].getKey() == key)	keyNodes[pos].insert(val);
		else{
			for(int j = filled; j > pos; j--){
				keyNodes[j] = keyNodes[j-1];
			}
				
			keyNodes[pos].setKey(key);
			keyNodes[pos].setValues(vector<string>(0));
			keyNodes[pos].insert(val);	
			filled++;
		}	

		if(isOverflow()) splitNode(path, root);				
	}
	else{
		path.push(this);

		BPTreeNode* nextNode = findPosition(key);
		nextNode->insert(key, val, path, root);
	}
}

/** 
	Split procedure called when a node overflows. It is cut into 2.
	If a node is leaf the right child includes the center, else it does not
	Also if the root to leaf path stack is empty it means that a new root is created, so update external root pointer to tree 
	Else if stack is not empty recursively insert the newly created center key object into nodes from path stack bottom up
*/
void BPTreeNode::splitNode(stack<BPTreeNode*>& path, BPTreeNode*& root){
	int half = (order+1)/2;
	int prefill = 1;

	BPTreeNodeElement* rightChildKeys = new BPTreeNodeElement[order+1];
	BPTreeNodeElement* center = new BPTreeNodeElement();
	
	BPTreeNode* right = new BPTreeNode(order, isLeaf, rightChildKeys);

	center->setKey(keyNodes[half].getKey());
	center->setLeft(this);
	center->setRight(right);

	if(isLeaf){
		prefill = 0;
		right->setNext(this->next);
		if(this->next) this->next->setPrev(right);

		this->next = right;
		right->setPrev(this);
	}

	for(int j = half+prefill; j <= order; j++){
		rightChildKeys[j-half-prefill] = keyNodes[j];
		keyNodes[j].initialize(-1, nullptr, nullptr);
	}

	right->setFilled(order-half-prefill+1);
	filled = half;
		
	if(path.empty()){
		BPTreeNodeElement* keys = new BPTreeNodeElement[order+1];
		keys[0] = *center;
	
		BPTreeNode* updated_root = new BPTreeNode(order, false, keys);
		updated_root->setFilled(1);

		root = updated_root;
	}
	else{
		BPTreeNode* parent = path.top(); path.pop();
		parent->insert(center, path, root);
	}

	return;
}

/** 
	Search procedure for B+ tree.
	Traverse top down to leaf from root
*/
void BPTreeNode::search(double key, vector<string>& result){
	if(isLeaf){
		bool notFound = true;

		for(int i = 0; i < filled; i++){
			if(keyNodes[i].getKey() == key){
				notFound = false;

				vector<string> values = keyNodes[i].getValues();
				result.insert(result.end(), values.begin(), values.end());

				break;
			}
		}
			
		if(notFound) result.push_back("Null");
	}
	else{
		BPTreeNode* nextNode = findPosition(key);
		nextNode->search(key, result);
	}

	return;
}

/** 
  	Range search procedure for B+ tree. Returns all (key, value) pairs with key in [key1, key2]
*/
void BPTreeNode::rangeSearch(double key1, double key2, vector<string>& result){
	if(isLeaf){
		for(int i = 0; i < filled; i++){
			if(keyNodes[i].getKey() > key2) return;

			if(keyNodes[i].getKey() >= key1 && keyNodes[i].getKey() <= key2){
				vector<string> values = keyNodes[i].getValues();

				for(int j = 0; j < (int)values.size(); j++){
					ostringstream s;
					s << "(" << keyNodes[i].getKey() << "," << values[j] << ")";
					result.push_back(s.str());
				}
			}
		}

		if(next) next->rangeSearch(key1, key2, result);	
	}
	else{
		BPTreeNode* nextNode = findPosition(key1);
		nextNode->rangeSearch(key1, key2, result);
	}
}

/** Utility method to find position of a key object in an array of key objects */

BPTreeNode* BPTreeNode::findPosition(double k){
	if(keyNodes[0].getKey() > k) return keyNodes[0].getLeft();

	for(int i = 0; i < filled-1; i++){
		if(keyNodes[i].getKey() <= k && keyNodes[i+1].getKey() > k)  return keyNodes[i].getRight();
	}

	return keyNodes[filled-1].getRight();
}
