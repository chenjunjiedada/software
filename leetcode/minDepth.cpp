/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode *root) {
        int depth, last, visit, total;
        TreeNode *p;
        if(!root) return 0;
        
        queue<TreeNode *> q;
        
        q.push(root);
        total = 1;
        visit = 0;
        depth = 0;
        last = 1;
        while (!q.empty()) {
            p = q.front();
            q.pop();
            if(!p->left && !p->right) return depth+1;
            visit ++;
            if(p->left) {
                q.push(p->left);
                total ++;
            }
            if(p->right) {
                q.push(p->right);
                total ++;
            }
            if(visit == last){
                depth ++;
                last = total;
            }
            
            
        }

    }
};
