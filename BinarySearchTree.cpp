#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include"./QueueByArray.cpp"
#include"./BinaryTree.cpp"

using namespace std;

template <class T>
class TreeNode
{
public:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	int count = 1;
	TreeNode(T _data) : data(_data), left(NULL), right(NULL) {}
	void updateCount(int val) {
		this->count += val;
	};
};

template <class T>
class NodeAndParent
{
public:
	TreeNode<T>* node;
	TreeNode<T>* parent;
	bool left;

	void print()
	{
		cout << endl
			<< "NODE: " << this->node->data << " PARENT: " << parent->data << " Left: " << left << endl;
	}
	// NodeAndParent(TreeNode<T>* _node,TreeNode<T>* _parent, bool _left):node(_node),parent(_parent),left(_left){
};

template <class T>
class BinarySearchTree : public BinaryTree<T>
{

public:
	//0->allowDublication , 1->donotAllowDublication, 2->addCounter
	int dublicationMethod;
	BinarySearchTree() {}

	BinarySearchTree(int _dublicationMethod) {
		if (_dublicationMethod == 1 || _dublicationMethod == 2) {
			dublicationMethod = _dublicationMethod;
		}
		else {
			dublicationMethod = 0;
		}
	}
	void insert(T _data)
	{
		TreeNode<T>* newNode = new TreeNode<T>(_data);
		if (this->root == NULL)
		{
			this->root = newNode;
			++this->numOfNodes;
			return;
		}
		else
		{
			TreeNode<T>* currentNode = this->root;
			while (currentNode != NULL)
			{
				if (currentNode->data > _data)
				{
					if (currentNode->left == NULL)
					{
						currentNode->left = newNode;
						++this->numOfNodes;
						return;
					}
					else
					{
						currentNode = currentNode->left;
					}
				}
				else if (currentNode->data == _data && dublicationMethod != 0) {
					if (this->dublicationMethod == 1) {
						cout << "Item " << _data << " Already Exist And This Tree Donot Allow Dublication\n";
						return;
					}
					else if (this->dublicationMethod == 2) {
						currentNode->updateCount(1);
						++this->numOfNodes;
						return;
					}
				}
				else
				{
					if (currentNode->right == NULL)
					{
						currentNode->right = newNode;
						++this->numOfNodes;
						return;
					}
					else
					{
						currentNode = currentNode->right;
					}
				}
			}
		}
	}

	TreeNode<T>* find(T _data)
	{
		TreeNode<T>* currentNode = this->root;
		while (currentNode != NULL)
		{
			if (currentNode->data == _data)
				return currentNode;
			else if (currentNode->data > _data)
				currentNode = currentNode->left;
			else if (currentNode->data < _data)
				currentNode = currentNode->right;
		}
		cout << "Item Not Found\n";
		return NULL;
	}
	NodeAndParent<T>* findNodeAndParent(T _data)
	{
		TreeNode<T>* currentNode = this->root;
		TreeNode<T>* parentNode = NULL;
		bool left = false;

		NodeAndParent<T>* returnedObj = new NodeAndParent<T>();

		while (currentNode != NULL)
		{
			if (currentNode->data == _data)
			{
				returnedObj->node = currentNode;
				returnedObj->parent = parentNode;
				returnedObj->left = left;
				return returnedObj;
			}
			if (currentNode->data > _data)
			{
				parentNode = currentNode;
				left = true;
				currentNode = currentNode->left;
			}
			else
			{
				parentNode = currentNode;
				left = false;
				currentNode = currentNode->right;
			}
		}

		delete returnedObj;
		return NULL;
	}


	void deleteNode(T _data)
	{
		NodeAndParent<T>* foundNodeAndParent = this->findNodeAndParent(_data);
		if (!foundNodeAndParent) {
			cout << "Node not found\n";
			return;
		}

		TreeNode<T>* foundNode = foundNodeAndParent->node;

		if (this->dublicationMethod == 2 && foundNode->count > 1) {
			foundNode->updateCount(-1);
			return;
		}
		// CASE 1:  Node Have two children
		if (foundNode->left != NULL && foundNode->right != NULL)
		{
			TreeNode<T>* currentNode = foundNode->right;
			TreeNode<T>* parentNode = foundNode;
			while (currentNode->left != NULL)
			{
				parentNode = currentNode;
				currentNode = currentNode->left;
			}
			if (parentNode == foundNode)
			{
				foundNode->right = currentNode->right;
			}
			else
			{
				parentNode->left = currentNode->right;
			}
			foundNode->data = currentNode->data;
			delete currentNode;
			--this->numOfNodes;

		}
		// CASE 2:  Node Have one child
		else if (foundNode->left != NULL ^ foundNode->right != NULL)
		{
			TreeNode<T>* replacedNode = NULL;
			if (foundNode->left != NULL)
			{
				replacedNode = foundNode->left;
			}
			else if (foundNode->right != NULL)
			{
				replacedNode = foundNode->right;
			}
			foundNode->data = replacedNode->data;
			foundNode->right = replacedNode->right;
			foundNode->left = replacedNode->left;
			delete replacedNode;
			--this->numOfNodes;
		}
		// CASE 3:  Node Donot Have children
		else if (foundNode->left == NULL && foundNode->right == NULL)
		{
			TreeNode<T>* parentNode = foundNodeAndParent->parent;
			if (parentNode == NULL)
				this->root = NULL;
			if (parentNode->left == foundNode)
				parentNode->left = NULL;
			if (parentNode->right == foundNode)
				parentNode->right = NULL;
			delete foundNode;
			--this->numOfNodes;
		}
	}

public:
	void balance()
	{
		T* arr = new T[this->numOfNodes];
		int index = 0;
		this->inOrderToArrayHelper(arr, this->root, index);
		this->root = recursiveBalance(0, this->numOfNodes - 1, arr);
		delete[] arr;
	}

private:
	void inOrderToArrayHelper(T* arr, TreeNode<T>* currentNode, int& i)
	{
		if (currentNode == NULL)
			return;
		inOrderToArrayHelper(arr, currentNode->left, i);
		for (int c = 0; c < currentNode->count; c++) {
			arr[i++] = currentNode->data;
		}


		inOrderToArrayHelper(arr, currentNode->right, i);
	}

private:
	TreeNode<T>* recursiveBalance(int start, int end, T* arr)
	{
		if (start > end)
			return NULL;
		int mid = (start + end) / 2;
		TreeNode<T>* newNode = new TreeNode<T>(arr[mid]);
		newNode->left = recursiveBalance(start, mid - 1, arr);
		newNode->right = recursiveBalance(mid + 1, end, arr);
		return newNode;
	}
};
//int main()
//{
//	BinarySearchTree<int> bst(2);
//	bst.insert(4);
//	bst.insert(7);
//
//	bst.insert(2);
//	bst.insert(4);
//	bst.insert(3);
//	bst.insert(4);
//
//	bst.insert(6);
//
//	cout << "Before balance:\n";
//	bst.printTree();
//	cout << endl << bst.height() << endl;
//	bst.balance();
//
//	cout << "\nAfter balance:\n";
//	bst.printTree();
//	cout << endl << bst.height() << endl;
//
//}
