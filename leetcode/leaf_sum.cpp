/**
 * Definition for binary tree
 */

#include <iostream>
#include <stdio.h>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
	public: 
		int sum;
		int mid ;
	public:
		Solution() {
			sum = 0;
			mid = 0;
		}

public:
    int sumNumbers(TreeNode *root) {
		if (!root) 
			return 0;

		if (!root->left && !root->right) {
			sum += mid + root->val;
			return sum;
		}

		mid += root->val;
		mid *= 10;
		if (root->left)
			sumNumbers(root->left);
		if (root->right)
			sumNumbers(root->right);
		mid /= 10;
		mid-=root->val;

		return sum;
	}

};

int main() {

	TreeNode a(1);
	TreeNode b(2);
	TreeNode c(3);
	
	TreeNode d(4);
	TreeNode e(5);

	a.left = &b; a.right = &c;
	b.left = &d; b.right = &e;

	Solution s;
	cout<< s.sumNumbers(&a)<< endl;
	
	return 0;
}
