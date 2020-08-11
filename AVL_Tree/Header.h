#pragma once
#include <memory>
#include <algorithm>
#include <list>
#include <iomanip>
#include <math.h>
#include <vector>

namespace VGP244 {
	template <typename T>
	struct Node
	{
		T data;
		std::shared_ptr<Node<T>> left;
		std::shared_ptr<Node<T>> right;
		uint8_t height;
		Node(T k) : data(k), left(nullptr), right(nullptr), height(1)
		{}
	};

	template<typename T>
	//using pNode_t = std::shared_ptr<Node<T>>;
	using pNode_t = std::shared_ptr<Node<T>>;
	template <typename T>
	class AVL
	{
	public:
		AVL() : root(nullptr) {}

		void insert(T val)
		{
			root = insert(root, val);
		}

		// removes the node with value val, if it exists in the tree. It returns true if delelted, otherwise return false
		bool remove(T val)
		{
			if (find(val))
			{
				root = remove(val, root);
				std::cout << "The node " << val << " is removed" << std::endl;
				return true;
			}
			return false;
		}

		pNode_t<T> find(T val)
		{
			if (find(val, root)!=nullptr)
			{
				//std::cout << "The node " << val << " is found" << std::endl;
				
				return find(val, root);
			}
			else
			{
				std::cout << "The node " << val << " is not found" << std::endl;
				return nullptr;
			}
		
		
		}
		int TreeHeight()
		{
			return  GettreeHeight(root);
		}

		void printTree()
		{
			printNode(root);
		}

		void Postorderprint()
		{
			Postorderprint(root);
		}


		void Inorderprint()
		{
			orderprint(root);
		}


		pNode_t<T> levelcopy(pNode_t<T> p)
		{
			pNode_t<T> newnode;
			newnode = std::make_shared<Node<T>>(p->data);

			newnode->left = std::make_shared<Node<T>>(p->left->data);
			newnode->right = std::make_shared<Node<T>>(p->right->data);

			newnode->left->left = std::make_shared<Node<T>>(p->left->left->data);
			newnode->left->right = std::make_shared<Node<T>>(p->left->right->data);
			newnode->right->left = std::make_shared<Node<T>>(p->right->left->data);
			newnode->right->right = std::make_shared<Node<T>>(p->right->right->data);
			
			newnode->left->left->left = std::make_shared<Node<T>>(p->left->left->left->data);
			newnode->left->left->right = std::make_shared<Node<T>>(p->left->left->right->data);
			newnode->left->right->left = std::make_shared<Node<T>>(p->left->right->left->data);
			newnode->left->right->right = std::make_shared<Node<T>>(p->left->right->right->data);
			newnode->right->left->left = std::make_shared<Node<T>>(p->right->left->left->data);
			newnode->right->left->right = std::make_shared<Node<T>>(p->right->left->right->data);
			newnode->right->right->left = std::make_shared<Node<T>>(p->right->right->left->data);
			newnode->right->right->right = std::make_shared<Node<T>>(p->right->right->right->data);

	
			return newnode;

		}

		pNode_t<T> Getroot()
		{
			return root;
		}

		void Setroot(pNode_t<T> p)
		{
			root = p;
		}

	private:
		pNode_t<T> root;




		int GettreeHeight(pNode_t<T> p)
		{
			if (p == nullptr)
			{
				return 0;
			}

			int leftheight = GettreeHeight(p->left);
			int rightheight = GettreeHeight(p->right);
			return std::max(leftheight, rightheight) + 1;
		}


		int8_t GetHeight(pNode_t<T> p)
		{
			return p ? p->height : 0;
		}

		int8_t BalanceFactor(pNode_t<T> p)
		{
			if (!p)
				return 0;
			return GetHeight(p->right) - GetHeight(p->left);
		}

		pNode_t<T> remove(T val, pNode_t<T> p)
		{
			if (!p)
			{
				return std::make_shared<Node<T>>(val);
			}
			if (val < p->data)
			{
				p->left = remove(val, p->left);
			}
			else if (val > p->data)
			{
				p->right = remove(val, p->right);
			}
			else
			{
				pNode_t<T> q = p->left;
				pNode_t<T> r = p->right;
				//std::cout << p.use_count();
				p.reset();
				//std::cout << p.use_count();
				if (!r)
					return q;
				pNode_t<T> minelement = findminright(r);
				minelement->right = removeminelemnet(r);
				minelement->left = q;
				return balance(minelement);
			}
			return balance(p);

		
		}

		pNode_t<T> removeminelemnet(pNode_t<T> p)
		{
			if (p->left == nullptr)
			{
				return p->right;
			}
			p->left = removeminelemnet(p->left);
			return balance(p);
		
		}

		pNode_t<T> findminright( pNode_t<T> p)
		{
			return p->left ? findminright(p->left) : p;
		
		}


		pNode_t<T> find(T val, pNode_t<T> p)
		{
			if (p != nullptr)
			{
				if (val == p->data)
				{
					return p;
				}
				else if (val < p->data)
				{
					return find(val, p->left);
				}
				else
				{
					return find(val, p->right);
				}
			}
			else
			{
				//std::cout << "The data is not found" << std::endl;
				return nullptr;
			}

		
		}


		void ComputeHeight(pNode_t<T> p)
		{
			int8_t h1 = GetHeight(p->left);
			int8_t h2 = GetHeight(p->right);
			p->height = std::max(h1, h2) + 1;
		}

		pNode_t<T> RotateRight(pNode_t<T> p)
		{
			pNode_t<T> q = p->left;
			p->left = q->right;
			q->right = p;
			ComputeHeight(p);
			ComputeHeight(q);
			return q;
		}

		pNode_t<T> RotateLeft(pNode_t<T> p)
		{
			pNode_t<T> q = p->right;
			p->right = q->left;
			q->left = p;
			ComputeHeight(p);
			ComputeHeight(q);
			// not implemented yet
			return q;
		}

		pNode_t<T> balance(pNode_t<T> p)
		{
			// double rotation not implemented yet! Student must implemented it here.
			ComputeHeight(p);
			auto p_balanceF = BalanceFactor(p);
			if (p_balanceF == 2)
			{
				if (BalanceFactor(p->right) < 0)
				{
					p->right = RotateRight(p->right);
				}// here check to see if you need to do one internal rotation to right
				return RotateLeft(p);
			}
			else if (p_balanceF == -2)
			{
				if (BalanceFactor(p->left) > 0)
				{
					p->left = RotateLeft(p->left);
				}// here check to see if you need to do one internal rotation to left
				return RotateRight(p);
			}

			return p;
		}
		pNode_t<T> insert(pNode_t<T> p, T val)
		{
			if (!p)
				return std::make_shared<Node<T>>(val);

			if (val < p->data)
				p->left = insert(p->left, val);
			else
				p->right = insert(p->right, val);

			return balance(p);
		}


		// pretty print a tree using space offset based on height. Pretty print means the tree should be printed
		// out on command line as usually tree structures are depicted, meaning root is the at top middle and each layer
		// is printed bellow it with proper distance among them. You should also use character / and \ to represent links
		// between parent and children.
		void printNode(pNode_t<T> node)
		{
			int maxlevel = maxLevel(node);

			std::vector <pNode_t<T>> vectortree;
			vectortree.push_back(node);
			printNodeInternal(vectortree, 1, maxlevel);

			// not implemented yet!
		}

		void printNodeInternal(std::vector<pNode_t<T>> nodes, int level, int maxLevel)
		{
			if (nodes.empty() || isAllElementsNull(nodes))
			{
				return;

			}



			int floor = maxLevel - level;
			int endgeLines = (int)pow(2, (std::max(floor - 1, 0)));
			int firstSpaces = (int)pow(2, (floor)) - 1;
			int betweenSpaces = (int)pow(2, (floor + 1)) - 1;

			printspaces(firstSpaces);
			std::vector<pNode_t<T>> newNodes;
			for(pNode_t<T> node : nodes) {
				if (node != nullptr) {
					std::cout << node->data;
					newNodes.push_back(node->left);
					newNodes.push_back(node->right);
				}
				else {
					newNodes.push_back(nullptr);
					newNodes.push_back(nullptr);
					std::cout<<" ";
				}

				printspaces(betweenSpaces);
			}
			std::cout<< std::endl;
			for (int i = 1; i <= endgeLines; i++) {
				for (int j = 0; j < nodes.size(); j++) {
					printspaces(firstSpaces - i);
					if (nodes[j] == nullptr) {
						printspaces(endgeLines + endgeLines + i + 1);
						continue;
					}

					if (nodes[j]->left != nullptr)
						std::cout<<"/";
					else
						printspaces(1);

					printspaces(i + i - 1);

					if (nodes[j]->right != nullptr)
						std::cout<<"\\";
					else
						printspaces(1);

					printspaces(endgeLines + endgeLines - i);
				}

				std::cout << std::endl;
			}

			printNodeInternal(newNodes, level + 1, maxLevel);
		
		}

		int maxLevel(pNode_t<T> node) 
		{
			if (node == nullptr)
				return 0;

			return std::max(maxLevel(node->left),maxLevel(node->right)) + 1;
		}

		void printspaces(int count) 
		{
			for (int i = 0; i < count; i++)
				std::cout << " ";
		}
		bool isAllElementsNull(std::vector<pNode_t<T>> vector)
		{
			for(pNode_t<T> val : vector)
			{
				if (val != nullptr)
					return false;
			}
			return true;

		}
		void Postorderprint(pNode_t<T> node)
		{
			if (node != nullptr)
			{
				Postorderprint(node->left);
				Postorderprint(node->right);
				std::cout << node->data << " ";
				
			}
		}

		void Inorderprint(FILE *file,  pNode_t<T> node)
		{
		

			if (node != nullptr)
			{
				Inorderprint(file,node->left);
				//std::cout << node->data << " ";
				fprintf(file, "%d\n", node->data);
				
				Inorderprint(file,node->right);
				

			}
		}

		void orderprint(pNode_t<T> node)
		{
			errno_t err;
			FILE* outfile;
			err=fopen_s(&outfile,"data.txt", "w");
			//if(err)
			Inorderprint(outfile,node);
			fclose(outfile);
		}

	};

} // namespace VGP244