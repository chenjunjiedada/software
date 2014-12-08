#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {

	public:	
		Solution() {
		res = 0;
		start = 0;
	}
	public:
		int **res;
		int len;
		int start;

    public: 
		void initres(int len) {
			this->len = len;
			int i, j;
			res = new int*[len];
			for (i = 0 ; i < len; i++) {
				res[i] = new int[len];
			}

			for (i = 0 ; i < len ; i++ ) {
				for (j = 0 ; j < len ; j++) {
					res[i][j] = 0;
				}
			}
		}
	public: 
		void showres() {
			int i, j;
			for (i = 0 ; i < len ; i++ ) {
				for (j = 0 ; j < len ; j++) {
					cout << res[i][j] << " "; 
				}
				cout << endl;
			}
			cout << endl;
		}

	public:
		bool wordBreak(string s, unordered_set<string> &dict) {
		int i, j;
		string substr, remain;

		if (!res) 
			initres(s.length());

		int len = s.length();

		if (s.size() == 0) 
			return false;

		/* res[0][len] = res[0][i] && res[i][len]*/
        for (i = 0; i < len; i++) {
			for (j = 0 ; j < len - i ; j++ ) {
				substr = s.substr(i, j+1);
				if (dict.find(substr) != dict.end()) {
					res[i][j] = true; 
					if ( i>0 && res[0][i-1]) res[0][i+j] = true;
				}

			}
		}

		return res[0][len-1];
    }
};

int main() 
{
	unordered_set<string> dict;
	dict.insert("leet");
	dict.insert("code");
	dict.insert("a");
	dict.insert("aa");

	string s1, s2;
	string str = "leetcode";

	Solution s;
	if (s.wordBreak(str, dict)) 
		cout << "true" << endl;

	s.showres();

	return 0;

}
