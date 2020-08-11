#include <iostream>
#include<random>

using namespace std;
class BST
{
	struct Node {
		int data;
		struct Node *left, *right;
		Node(int val) :data(val), left(nullptr), right(nullptr) {}
	};
	struct Node* root;


	void insert(Node *&node,int key)
	{

		if (node == nullptr)
		{
			node = new Node(key);

		}
		else if (node->data <= key)
		{
			
			insert(node->right,key);

		}
		else if (node->data > key)
		{
			insert(node->left, key);
		}

	}

	void print(struct Node *node)
	{
		if (node != nullptr)
		{
			print(node->left);
			cout << node->data << " ";
			print(node->right);
		}
	}


	bool find(struct Node *node,int value)
	{
		if (node == nullptr)
		{
			return false;
		}
		else if (node->data == value)
		{
			return true;

		}
		else if (node->data < value)
		{
			return find(node->right, value);
		}
		else
		{
			return find(node->left, value);
		}


	}	
	
	void levelsum(struct Node *node, int level, int sum[])
	{
		if (node == nullptr)
		{
			return;
		}
		else
		{
			sum[level] += node->data;
			levelsum(node->left, level + 1, sum);
			levelsum(node->right, level + 1, sum);
		}

	}
	void Destroy(struct Node *node)
	{
		if (node == nullptr)
		{
			return;

		}
		else
		{
			Destroy(node->left);
			Destroy(node->right);
			cout << "Destroy node: " << node->data << endl;
			delete node;

		}
	
	
	}
	int GetLevel(struct Node *node)
	{
		int leftnode = 0, rightnode = 0;
		if (node == nullptr)
		{
			return 0;
		}
		leftnode = GetLevel(node->left);
		rightnode = GetLevel(node->right);
		return leftnode > rightnode ? leftnode + 1 : rightnode + 1;
	}

	int MaxLevelSumBST(struct Node *node, int level)
	{
		int *sum = new int[level];
		for (int i = 0; i < level; i++)
		{
			sum[i] = 0;
		}
		levelsum(node, 0, sum);
		cout << "All sum of each level is shown as below:" << endl;
		for (int i = 0; i < level; i++)
		{
			cout << sum[i] << endl;

		}
		int maxnum = sum[0];
		for (int i = 0; i < level; i++)
		{
			if (maxnum <= sum[i])
			{
				maxnum = sum[i];
			}

		}
		delete[] sum;
		return maxnum;
	}


public:
	BST() {}
	~BST() { Destroy(root); }
	bool findnode(int value)
	{
	
		return find(root, value);
	
	}
	void insertnode(int value)
	{
		insert(root, value);

	}
	void print_tree()
	{
		print(root);
		cout << endl;
	}



	int GetallLevel()
	{
		return GetLevel(root);
	
	}



	int MaxLevelSum()
	{
		int level= GetallLevel();
		return MaxLevelSumBST(root, level);
	}

};

int main()
{
	BST bsttree;
	srand(0);
	//int sum[3] = {0};
	/*
			  5
		   /     \
		  3       7
		 /  \    /  \
	   2     4  6    8
	bsttree.insertnode(5);
	bsttree.insertnode(3);
	bsttree.insertnode(2);
	bsttree.insertnode(4);
	bsttree.insertnode(7);
	bsttree.insertnode(6);
	bsttree.insertnode(8);
*/
	cout << "Random number insert: ";
	for (int i = 0; i < 62; i++)
	{
		int number = rand() % 100;
		bsttree.insertnode(number);
		cout << number << " ";
	}
	cout << endl << endl;
	cout << "All nodes of the BST are: ";
	bsttree.print_tree();
	cout << endl;
	int number = 36;
	cout << "Does value " << number << " in the BST?: " << boolalpha << bsttree.findnode(number) << endl;
	number = 35;
	cout << "Does value " << number << " in the BST?: " << boolalpha << bsttree.findnode(number) << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "The maximum sum from all level is: " << bsttree.MaxLevelSum() << endl;
	system("pause");
	return 0;
}