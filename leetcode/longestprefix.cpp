#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        string ret;
        int i, j;
        char tmp;
        string str;
        j=0;
        while(1) {
            tmp = strs[0][j];
            for (i=1;i<strs.size() ;i++) {
                if (tmp != strs[i][j])
                    break;
            }
            if (i!=strs.size()) break; 
            ret += tmp;
            j++;
        }
        return ret;
    }
};


int main() 
{
	string longestprefix;
	vector<string> strs;
	strs.push_back("hello");
	strs.push_back("helo");
	strs.push_back("hewillbe");

	Solution s;
	longestprefix = s.longestCommonPrefix(strs);

	cout << longestprefix<< endl;

return 0;
}
