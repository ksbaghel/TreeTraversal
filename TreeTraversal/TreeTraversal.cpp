// TreeTraversal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <queue>
#include <map>

using namespace std;

struct TNode {
	int key;
	TNode* left;
	TNode* right;
};

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; } 
TNode* newNode(int val)
{
	TNode* temp = new TNode();
	temp->key = val;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

void preOrder_Recursive(TNode* root)
{
	//preOrder : N ->L->R
	if (!root) return;
	cout << root->key << " ";
	preOrder_Recursive(root->left);
	preOrder_Recursive(root->right);
}

void preOrder_Iterative(TNode* root)
{
	if (!root) return;
	//keeping moving left and pring the node..and push the right subtree into stack
	stack<TNode*> s;
	TNode* curr = root;
	while (!s.empty() || curr)
	{
		if (curr)
		{
			cout << curr->key << " ";
			if (curr->right)
			{
				s.push(curr->right);
			}
			curr = curr->left;
		}
		else {
			curr = s.top();
			s.pop();
		}
	}
	cout << endl;
}

void InOrder_Recursive(TNode* root)
{
	//INorder : L N R
	if (!root) return;
	
	InOrder_Recursive(root->left);
	cout << root->key << " ";
	InOrder_Recursive(root->right);
}

void InOrder_Iterative(TNode* root)
{
	if (!root) return;

	stack<TNode*> s;
	TNode* curr = root;
	while (!s.empty() || curr)
	{
		if (curr)
		{
			s.push(curr);
			curr = curr->left;
		}
		else {
			//No more left..pop the stack..basically move back to parent
			curr = s.top();
			s.pop();
			//print the parent
			cout << curr->key << " ";
			//we have already covered it leftsubtree..time to cover right subtree
			curr = curr->right;
		}
	}
	cout << endl;
}

void postOrder_Recursive(TNode* root)
{
	//postorder - > L -> R -> N
	if (!root) return;
	
	postOrder_Recursive(root->left);
	postOrder_Recursive(root->right);
	cout << root->key << " ";
}

void postOrder_Iterative(TNode* root)
{
	if (!root) return;
	stack<TNode*> s1, s2;

	TNode* curr = root;
	while (!s1.empty() || curr)
	{
		if (curr)
		{
			s1.push(curr);
			if (curr->right)
			{
				s2.push(curr->right);
			}
			curr = curr->left;
		}
		else {
			curr = s1.top();
			if (curr->right)
			{
				if (!s2.empty() && (curr->right == s2.top()))
				{
					curr = s2.top();
					s2.pop();
				}
				else {
					cout << curr->key << " ";
					s1.pop();
					curr = NULL;
				}
			}
			else {
				cout << curr->key << " ";
				s1.pop();
				curr = NULL;
			}
		}
	}
	cout << endl;
}

void postOrder_Iterative2(TNode* root)
{
	if (!root) return;
	stack<TNode*> s1, s2;

	TNode* curr = root;
	s2.push(curr);
	if (curr->left) s1.push(curr->left);
	if (curr->right) s1.push(curr->right);

	while (!s1.empty())
	{
		curr = s1.top();
		s1.pop();
		s2.push(curr);
		if (curr->left) s1.push(curr->left);
		if (curr->right) s1.push(curr->right);
	}

	//now print the elements in s2
	while (!s2.empty())
	{
		curr = s2.top();
		s2.pop();
		cout << curr->key << " ";
	}
	cout << endl;
}

void levelOrder(TNode* root)
{
	if (!root) return;

	queue<TNode*> Q;
	TNode* curr = root;
	cout << curr->key << " ";
	if (curr->left) Q.push(curr->left);
	if (curr->right) Q.push(curr->right);

	while (!Q.empty())
	{
		curr = Q.front();
		Q.pop();
		cout << curr->key << " ";
		if (curr->left) Q.push(curr->left);
		if (curr->right) Q.push(curr->right);
	}
	
	cout << endl;
}

void levelOrder_LinebyLine(TNode* root)
{
	if (!root) return;

	queue<TNode*> Q;
	TNode* curr = root;
	cout << curr->key << endl;
	if (curr->left) Q.push(curr->left);
	if (curr->right) Q.push(curr->right);
	//insert NULL as linebreaker
	Q.push(NULL);
	while (Q.size() != 1) // 1 because we inserted NULL for sure
	{
		curr = Q.front();
		Q.pop();
		if(curr)
		{
			cout << curr->key << " ";
			if (curr->left) Q.push(curr->left);
			if (curr->right) Q.push(curr->right);
		}
		else { //its a line breaker
			cout << endl;
			Q.push(NULL);
		}
	}
	cout << endl;
}

void levelOrder_Spiral(TNode* root)
{
	if (!root) return;
	stack<TNode*> s1, s2;
	TNode* curr = root;
	s1.push(curr);
	
	while (!s1.empty() || !s2.empty())
	{
		while (!s1.empty())
		{
			curr = s1.top();
			s1.pop();
			cout << curr->key << " ";
			if (curr->right) s2.push(curr->right);
			if (curr->left) s2.push(curr->left);
		}
		cout << endl;
		
		while (!s2.empty())
		{
			curr = s2.top();
			s2.pop();
			cout << curr->key << " ";
			if (curr->left) s1.push(curr->left);
			if (curr->right) s1.push(curr->right);
		}
		cout << endl;
	}
	cout << endl;
}

void width(TNode* node, int w, int &minW, int &maxW)
{
	if (!node) return;
	minW = min(minW, w);
	maxW = max(maxW, w);
	width(node->left, w - 1, minW, maxW);
	width(node->right, w + 1, minW, maxW);
}
void printNodeAtWidth(TNode* node, int currW, int W)
{
	if (!node) return;
	if (currW == W)
	{
		cout << node->key << " ";
	}
	printNodeAtWidth(node->left, currW - 1, W);
	printNodeAtWidth(node->right, currW + 1, W);
}
void verticalOrder(TNode* root)
{
	if (!root) return;
	//first find the width of the tree
	int w=0, minW = 0, maxW = 0;
	width(root, w, minW, maxW);
	//now for each width level..print all the nodes
	for (w = minW; w <= maxW; w++)
	{
		printNodeAtWidth(root, 0, w);
		cout << endl;
	}
}

void visitNodesInOrder(TNode* node, int hd, map<int, vector<int> > &m)
{
	if (!node) return;
	//now insert this node into map
	m[hd].push_back(node->key);
	visitNodesInOrder(node->left, hd - 1, m);
	visitNodesInOrder(node->right, hd + 1, m);
}

void verticalOrder_HashMap(TNode* root)
{
	if (!root) return;
	map<int, vector<int> > m; //<HD, nodes>
	visitNodesInOrder(root, 0, m);
	//print the map
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		vector<int> v = (*it).second;
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}
}

void verticalOrder_levelOrder(TNode* root)
{
	//This algo maintain the order in which nodes appears in the vertical order...
	//in other algos... for the same width...node appearing in left subtree in printed first..irrespective of its hight
	if (!root) return;
	//visit nodes in level order and update their hd
	map<int, vector<int> > m; //<HD, nodes>
	queue<pair<TNode*, int> > Q;
	TNode* curr = root;
	Q.push(make_pair(curr, 0));
	while (!Q.empty())
	{
		pair<TNode*, int> p = Q.front();
		Q.pop();
		m[p.second].push_back(p.first->key);
		if (p.first->left) Q.push(make_pair(p.first->left, p.second - 1));
		if (p.first->right) Q.push(make_pair(p.first->right, p.second + 1));
	}

	//print the map
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		vector<int> v = (*it).second;
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}
}

int main()
{
	TNode* root = newNode(30);
	root->left = newNode(20);
	root->right = newNode(35);
	root->left->left = newNode(10);
	root->left->left->left = newNode(8);
	root->left->left->right = newNode(15);
	root->left->left->right->right = newNode(18);
	root->left->right = newNode(25);
	root->left->right->left = newNode(22);
	root->right->left = newNode(33);
	root->right->left->left = newNode(31);
	root->right->right = newNode(40);

	cout << "Inorder Recursive:     "; InOrder_Recursive(root); cout << endl;
	cout << "Inorder Iterative:     "; InOrder_Iterative(root);
	cout << endl;

	cout << "Preorder Recursive:    "; preOrder_Recursive(root); cout << endl;
	cout << "Preorder Iterative:    "; preOrder_Iterative(root);
	cout << endl;

	cout << "Postorder Recursive:   "; postOrder_Recursive(root); cout << endl;
	cout << "PostOrder Iterative:   "; postOrder_Iterative(root);
	cout << "PostOrder Iterative2:  "; postOrder_Iterative2(root);
	cout << endl;

	cout << "LevelOrder :           "; levelOrder(root);
	cout << "LevelOrder-linebyline: "; levelOrder_LinebyLine(root);
	cout << "LevelOrder Spiral:     "; levelOrder_Spiral(root);
	cout << endl;

	cout << "verticalOrder :        "; verticalOrder(root);
	cout << "verticalOrder_HashMap: "; verticalOrder_HashMap(root);
	cout << "verticalOrder_levelOrder: "; verticalOrder_levelOrder(root);


	

    return 0;
}

