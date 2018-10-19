// Capt Teal "Koala" Peterson
// 29 Nov 17
// Peterson_binary_tree.h
//
// struct declaration should be global, since member function 
//      node * btree::copy_tree()
// appears otside of class body
//
// Designed on Windows 10

/* Example Tree

		  -----------------------------67--------------------
	-----0-------------       	                            91
   	N       ----------24------- 	                       N  N
	        4             -----58-------
           N N       ----45----        64
		          --27---      53     N  N
			     N      42    N  N
			    	 36   N
				    N  N

*/

#include <iostream>

struct node
{
    int key_value;
    int data;
    node *left;
    node *right;
};

//---------------------------------------
class btree
{
	node *root;
	int	 total = 0; // total number of stored keys
	int sum = 0; // New,sum of all data, updated on insert/delete
	
	void destroy_tree(node *leaf);
	void insert(int key, node *leaf, int val); // Modified
	int  search(int key, node *leaf);
	void print_tree(node * t);
	node *copy_tree(node * t);
	void delete_(node * & tree, int item); // Modified
	void delete_node(node * & tree); // Modified
	void get_predecessor(node * tree, int & k, int & d);
    void print_vis(int depth, node * t);
	//int data_sum(node* L, node* R); // New V1
	int data_sum(node* t); // New V2
	int min_depth_(node* t); // New
	int max_depth_(node* t); // New

public:
	btree();
	btree(const btree &t);
	~btree();
	void insert(int key, int val); // Modified
	int  search(int key); // returns data associated with the key
						  // or -1 if not found
	void print();
	int  size();
	void delete_item(int item);
	void destroy_tree();
    void print_vis();
	int smallest_key(); // New
	int largest_key(); // New
	double easy_average(); // New
	double average_data(); // New
	int min_depth(); // New
	int max_depth();
};

//--------- definitions ------------
// normal constructor
btree::btree()
{
  root	= NULL;
  total = 0;
}

// copy constructor
btree::btree(const btree &t){
	root  = copy_tree(t.root);
	total = t.total;
}

// destructor
btree::~btree()
{
  destroy_tree();
}

void btree::destroy_tree()
{
	destroy_tree(root);
    root  = NULL;
    total = 0;
}

void btree::destroy_tree(node *leaf)
{
  if(leaf!=NULL)
  {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

void btree::insert(int key, node *leaf, int val)

{ if(key == leaf-> key_value){
    // the key already exists
	sum -= leaf->data; //***** my update ****  Added for average
	leaf-> data = val; // update the data
	sum += leaf->data; //***** my update ****  Added for average
	return;
  }
  if(key < leaf->key_value)
  {
    if(leaf->left!=NULL)
     insert(key, leaf->left, val);
    else
    {
      leaf->left=	new node;
      leaf->left->key_value	= key;
	  leaf->left->data		= val;
      leaf->left->left		= NULL; //Sets the left child of the node to null
      leaf->left->right		= NULL; //Sets the right child of the node to null
	  ++total;
	  sum += val; //***** my update ****  Added for average
    }  
  }
  else if(key > leaf->key_value)
  {
    if(leaf->right!=NULL)
      insert(key, leaf->right, val);
    else
    {
      leaf->right=	new node;
      leaf->right->key_value  = key;
	  leaf->right->data		  = val;
      leaf->right->left		  = NULL; //Sets the left child of the node to null
      leaf->right->right	  = NULL; //Sets the right child of the node to null
	  ++total;
	  sum += val; //***** my update ****  Added for average
    }
  }
}

void btree::insert(int key, int val)
{
	if (root != NULL)
		insert(key, root, val);
	else
	{
		root = new node;
		root->key_value = key;
		root->data = val;
		root->left = NULL;
		root->right = NULL;
		++total;
		sum += val; //***** my update ****  Added for average
	}
}

int btree::search(int key, node *leaf)
{
  if(leaf!=NULL)
  {
    if(key == leaf->key_value)
      return leaf->data;
    if(key < leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return -1;
}

int btree::search(int key)
{
  return search(key, root);
}

void btree::print_tree(node * t)
{
	if ( t != NULL ) {  // (Otherwise, there's nothing to print.)
		print_tree(t->left);			// Print items in left subtree.
		cout << "(key= "<< t->key_value << ", data= " << 
			    t-> data << ")\n"; // Print the root item.

		print_tree( t->right );			// Print items in right subtree.
	}
}

node * btree::copy_tree(node * t){
	
	if(!t) return NULL;
	
	node * p = new node;
	p-> key_value = t-> key_value;
	p-> data	  = t-> data;
	p-> left  = copy_tree(t-> left);
	p-> right = copy_tree(t-> right);
	return p;
}

void btree::print()
{
	cout << "Tree width " << total << endl;
	cout << "Tree data sum: " << sum << endl;
	cout << "nodes:\n";
	print_tree(root);
	cout << endl;
}

int btree::size()
{
	return total;
}

void btree::delete_item(int item){
	delete_(root, item);
}

void btree::delete_(node * & tree, int item){
	
	if(!tree) return;// item was not found
	
	if (item < tree-> key_value)
		delete_(tree->left, item);   // Look in left subtree.
	else if (item > tree-> key_value)
		delete_(tree->right, item);  // Look in right subtree.
	else 
		delete_node(tree);           // node found; call delete_node()
}

void btree::delete_node(node * & tree){
	// Deletes the node pointed to by tree.
	// The user's data in the node pointed to by tree is no 
	// longer in the tree.  If tree is a leaf node or has only one
	// non-NULL child pointer the node pointed to by tree is 
	// deleted; otherwise, the key_value is replaced by its 
	// logical predecessor and the predecessor's node is deleted.

	//deleteNode -> delete node, then replace with down/left one, down/right until NULL right node
	//delete 67 -> 67 will be replaced with 64

	{
	int k, d;
	node * tempPtr;
		
	tempPtr = tree;
	if (tree->left == NULL)
		{
			tree = tree->right;
			sum -= tempPtr->data; //***** my update ****  Added for average
			delete tempPtr;
			--total;
		}
	else if (tree->right == NULL)
		{
			tree = tree->left;
			sum -= tempPtr->data; //***** my update ****  Added for average
			delete tempPtr;
			--total;
		}
	else // tree has two children
		{
			get_predecessor(tree->left, k, d);
			tree-> key_value = k;
			tree-> data		 = d;
			delete_(tree->left, k);  // Delete predecessor node
		}
	}
}

void btree::get_predecessor(node * tree, int & k, int & d){
	// Sets data to the data member of the right-most node in tree.
	while (tree->right != NULL)
		tree = tree->right;
	k = tree->key_value;
	d = tree->data;
}

void btree::print_vis(){
    print_vis(0, root);
}

void btree::print_vis(int depth, node * t)
{
    if ( t != NULL ) {  // (Otherwise, there's nothing to print.)
        for(int i=0; i<depth;i++) cout<< ' ';
        cout << t->key_value << " \n";	// Print the root item.
        print_vis(depth+2, t->left);			// Print items in left subtree.
        print_vis(depth+2, t->right );			// Print items in right subtree.
    } 
    else {
		for(int i=0; i<depth;i++) cout<< ' ';
        cout<<"NULL\n";}
}


//****** Teal's Update ******

int btree::smallest_key() {
	// Traverses left side of tree until NULL is found, then returns value of that key
	if (root == NULL) {
		cout << "smallest_key(): Tree is empty." << endl;
		return 0;
	}

	node* tree = root;
	while (tree->left != NULL)
		tree = tree->left;
	return tree->key_value;
}

int btree::largest_key() {
	// Traverses right side of tree until NULL is found, then returns value of that key
	if (root == NULL) {
		cout << "largest_key(): Tree is empty." << endl;
		return 0;
	}// For the empty tree

	node* tree = root;
	while (tree->right != NULL)
		tree = tree->right;
	return tree->key_value;
	}

double btree::easy_average() {
	// Program modified to add/subtract data as nodes are inserted/deleted.
	// This sum used for providing the average.  Additional functions were created
	// below according to the specs of the assignment.
	if (root == NULL) {
		cout << "easy_average(): Tree is empty." << endl;
		return 0;
	}  //For the empty tree case
	else return (double) sum / total;
}

double btree::average_data() {
	//summation = root->data + data_sum(root->left, root->right);
	if (root == NULL) {
		cout << "average_data(): Tree is empty." << endl;
		return 0;
	}//For the empty tree
	else return (double) data_sum(root)/total;
}

/* data_sum() V1 - recursively decended into both child nodes at once.
   This option was more complicated than it needed to be, so went with V2
int btree::data_sum(node* L, node* R) {
	int leftTotal;
	int rightTotal;

	if (L != NULL) leftTotal = L->data + data_sum(L->left, L->right);
	else leftTotal = 0;
	
	if (R != NULL) rightTotal = R->data + data_sum(R->left, R->right);
	else rightTotal = 0;

	return leftTotal + rightTotal;
}*/

int btree::data_sum(node* t) {
	// data_sum() V2. Recursively adds sum of all child nodes to current node, then
	// returns that value.  If a child node is NULL, it adds 0 for that node.
	int leftTotal;
	int rightTotal;

	if (t->left != NULL) leftTotal = data_sum(t->left);
	else leftTotal = 0;

	if (t->right != NULL) rightTotal = data_sum(t->right);
	else rightTotal = 0;

	return t->data + leftTotal + rightTotal;
}


//*** Teal's Bonus Functions ***

int btree::min_depth() {
	//Public funciton that seeds recursive min_depth_() private function
	return min_depth_(root);
}

int btree::min_depth_(node* t) {
	//Returns minimum depth of left/right child nodes, counting itself as one.
	//If a node is NULL (or non-existent), it returns 0.
	int leftDepth;
	int rightDepth;

	if (t != NULL) {
		leftDepth = min_depth_(t->left) + 1;
		rightDepth = min_depth_(t->right) + 1;

		if (leftDepth < rightDepth) return leftDepth;
		else                        return rightDepth;
	}
	else return 0;
}

int btree::max_depth() {
	//Public funciton that seeds recursive min_depth_() private function
	return max_depth_(root);
}

int btree::max_depth_(node* t) {
	//Returns minimum depth of left/right child nodes, counting itself as one.
	//If a node is NULL (or non-existent), it returns 0.
	int leftDepth;
	int rightDepth;

	if (t != NULL) {
		leftDepth = max_depth_(t->left) + 1;
		rightDepth = max_depth_(t->right) + 1;

		if (leftDepth > rightDepth) return leftDepth;
		else                        return rightDepth;
	}
	else return 0;
}