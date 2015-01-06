#include <vector>
#include <queue>
#include <iostream>

using namespace std;
/**
 * Definition for binary tree
 */


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
};
class Solution {
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > s;
        queue<TreeNode* > q;
     
        TreeNode *p = 0; 
     
        if (!root) return s;
     
        int index = 0;
        int total = 1;
        int level_count = 1;
     
        vector<int> *tmp = new vector<int>();
        q.push(root);
        while(!q.empty()) {
            p = q.front();
            q.pop();
            index ++;
            tmp->push_back(p->val);

            if(p->left) {
                q.push(p->left);
                total ++;
            }
            if(p->right){
                q.push(p->right);
                total ++;
            }
            if(index == level_count) {
                level_count = total;
                s.insert(s.begin(),*tmp);
                tmp = new vector<int>();
            }
        }
        return s;
    }
};

class Solution {
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > s;
		vector<vector<int> >::iterator it;
        queue<TreeNode* > q;
        
        TreeNode *p;
        
        if (!root) return s;
        
        int index = 0;
        int total = 1;
        int level_count = 1;
        
        vector<int> tmp;
        q.push(root);
        while(!q.empty()) {
            p = q.front();
            q.pop();
            index ++;
            tmp.push_back(p->val);
            
            if(p->left) {
                q.push(p->left);
                total ++;
            }
            if(p->right){
                q.push(p->right);
                total ++;
            }
            if(index == level_count) {
				cout << "end" << endl;
                level_count = total;
				it = s.begin();

                s.insert(it, tmp);
				tmp.clear();
            }
        }
        
    }
};

int main() 
{
	struct TreeNode r;
	struct TreeNode rl;

	vector<vector<int> > an;

	r.val = 1;
	r.left = 0;
	r.right = 0;

	rl.val = 2;
	rl.left = 0;
	rl.right = 0;

	r.left = &rl;

	Solution s;
	an = s.levelOrderBottom(&r);
	int size = an.size();
	for (int i = 0; i < an.size(); i++) {
		for (int j = 0; j < an[i].size(); j++) {
			cout << an[i][j] << " ";
		}
		cout << endl;
	}

	

	return 0;
}
