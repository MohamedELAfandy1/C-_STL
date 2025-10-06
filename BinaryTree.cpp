#include<iostream>
#include<./QueueByArray>
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;
template <class T>
class TreeNode{
	public:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	
	TreeNode(T _data):data(_data),left(NULL), right(NULL){}
};

template <class T>
class BinaryTree{

	public:
	TreeNode<T>* root;	
	int numOfNodes;
	
	BinaryTree():root(NULL), numOfNodes(0){}

	TreeNode<T>* find(T _data){
		if(root == NULL){
			out<<"Tree Is EMPTY\n";
			return NULL;
		} 
		Queue<TreeNode<T>*> q1;
		q1.enqueue(this->root);
		while(!q1.isEmpty()){
			TreeNode<T>* currentNode = q1.dequeue() ;
			if(currentNode->data == _data )	return currentNode;
			else{
				if(currentNode->left != NULL)	q1.enqueue(currentNode->left);
				if(currentNode->right != NULL)	q1.enqueue(currentNode->right);
			}			
		}
		cout<<"ITEM NOT FOUND\n";
		return NULL;
				
	}
	
	void insert(T _data){
		if( root == NULL){
			TreeNode<T>* newNode = new TreeNode<T>(_data);
			root = newNode;
			++numOfNodes;
			return;
		}else{
			Queue<TreeNode<T>*> q1;	
			//Queue<TreeNode<T>*>* q1 = new Queue<TreeNode<T>*>();			
			q1.enqueue(root);
			while(!	q1.isEmpty() ){
				TreeNode<T>* currentNode = q1.dequeue();
				if(currentNode->left == NULL){
					currentNode->left= new TreeNode<T>(_data);
					++numOfNodes;
	
					break;
				}else{
					q1.enqueue(currentNode->left);
				}
				if(currentNode->right == NULL){
					currentNode->right= new TreeNode<T>(_data);
					++numOfNodes;
					break;
				}else{
					q1.enqueue(currentNode->right);
				}
				
			}
		}
	}

	void update(T node, T newData ){
		TreeNode<T>*  foundNode = this->find(node);
		if(foundNode!=NULL){
			foundNode->data = newData;	
		}
	}

	void deleteNode(T _data){
		if(root == NULL){
			cout<<"Tree Is EMPTY\n";
			return;
		} 
		
		Queue<TreeNode<T>*> q1;
		q1.enqueue(this->root);
		
		TreeNode<T>* targetNode =NULL;
		TreeNode<T>* lastParent = NULL;
		TreeNode<T>* lastNode=NULL;
		
		while(!q1.isEmpty()){
			TreeNode<T>* currentNode = q1.dequeue() ;
			if(currentNode->data == _data )	targetNode = currentNode;
			if(currentNode->left != NULL){
				lastParent = currentNode;
				q1.enqueue(currentNode->left);
			}	
			if(currentNode->right != NULL)	{
				lastParent = currentNode;
				q1.enqueue(currentNode->right);	
			}
			lastNode=currentNode;
		}
	   	
		if (targetNode == NULL) {
	        cout << "Node not found\n";
	        return;
	    }
		//to delete lastNode =>	avoid double deleting
	   if (targetNode == lastNode) {
	        if (lastParent != NULL) {
	            if (lastParent->left == lastNode) lastParent->left = NULL;
	            else if (lastParent->right == lastNode) lastParent->right = NULL;
	        } else {
	            root = NULL; //The only element in tree is root and i want to delete it
	        }
	        delete lastNode;
	        --numOfNodes;
	        return;
	    }
		
		targetNode->data = lastNode->data;
    	if (lastParent != NULL) {
	        if (lastParent->left == lastNode) {
	            delete lastParent->left;
	            lastParent->left = NULL;
	        } else if (lastParent->right == lastNode) {
	            delete lastParent->right;
	            lastParent->right = NULL;
        	}
        	--numOfNodes;
    	}				
	}

	
	void print(){
			if(root == NULL){
				cout<<"The Tree Is Empty\n";
			}else{
				Queue<TreeNode<T>*> q1;
				q1.enqueue(root);
				while(!q1.isEmpty()){
					TreeNode<T>* currentNode = q1.dequeue();
					cout<<currentNode->data<<" ";
					if(currentNode->left != NULL)	q1.enqueue(currentNode->left);
					if(currentNode->right != NULL)	q1.enqueue(currentNode->right);
				}
			}
		}
	
	int getNumOfNodes(){
		return numOfNodes;
	}
	
	int height() {
        return heightHelper(root);
    }
	private: int heightHelper(TreeNode<T>* currentNode) {
        if (currentNode == NULL)
            return 0;
        return 1 + std::max(heightHelper(currentNode->left), heightHelper(currentNode->right));
    }
	
	public: void preOrderTraverse(){
		preOrderTraverseHelper(root);
		cout<<endl;
	}
	private: void preOrderTraverseHelper(TreeNode<T>* currentNode){
		if(currentNode  == NULL)	return;
		cout<<currentNode->data<<" ";
		preOrderTraverseHelper(currentNode->left);
		preOrderTraverseHelper(currentNode->right);
		
	}	
	
	public: void inOrderTraverse(){
		inOrderTraverseHelper(root);
		cout<<endl;
	}
	private: void inOrderTraverseHelper(TreeNode<T>* currentNode){
		if(currentNode  == NULL)	return;
		inOrderTraverseHelper(currentNode->left);
		cout<<currentNode->data<<" ";
		inOrderTraverseHelper(currentNode->right);
		
	}
	
	public: void postOrderTraverse(){
		postOrderTraverseHelper(root);
		cout<<endl;
	}
	private: void postOrderTraverseHelper(TreeNode<T>* currentNode){
		if(currentNode  == NULL)	return;
		postOrderTraverseHelper(currentNode->left);
		postOrderTraverseHelper(currentNode->right);
		cout<<currentNode->data<<" ";
		
	}
	
    
};
int main() {
    BinaryTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    cout << "Level Order: ";
    tree.print();  // 10 20 30 40 50
    cout << endl;

    cout << "PreOrder: ";
    tree.preOrderTraverse(); // 10 20 40 50 30

    cout << "InOrder: ";
	tree.inOrderTraverse();	//40 20 50 10 30
	
	cout<<"Updating 20 to 22\n";
	tree.update(20,22);
	
	cout << "PostOrder: ";
	tree.postOrderTraverse();	//40 50 20 30 10
    
	cout << "Deleting 30...\n";
    tree.deleteNode(30);

    cout << "Level Order After Deletion: ";
    tree.print();
    cout << endl;

    cout << "Height: " << tree.height() << endl;
}


