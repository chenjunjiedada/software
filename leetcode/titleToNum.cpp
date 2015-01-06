#include <iostream>
using namespace std;

class Solution {
	public:
		int titleToNumber(string s) {
			int len = s.length();
			int i, res;
			cout << len << endl;
			if(!len) return 0;

			res = 0;
			for(i=0;i<len;i++) {
				res *= 26;
				res += s[i] -'A' + 1;
			}
			return res;
		}
};


int main() {
	int res;
	Solution s;
	res = s.titleToNumber("AB");
	cout <<res << endl;

	return 0;
}
