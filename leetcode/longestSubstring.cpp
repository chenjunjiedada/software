#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        char hash[128] = {0};
		int i, j;
		int maxLen = 0;
		int len;
		int start = 0;

        while(start < s.length()) {
            len = 0;
            for (i = start ; i < s.length(); i++) {
                if(!hash[s[i]]) {
                    len ++; 
                    hash[s[i]] = i + 1;
                } else {
                    if (len > maxLen) {
                        maxLen = len;
                    }

                    start = hash[s[i]];
                    memset(hash, 0, 128);
                    break;
                }   
            }   
            if (i == s.length()){
                if(len > maxLen) maxLen = len;
                break;
            } 
        }

		return maxLen;
        
    }
};



int main()
{
	/*
	string str = "hnwnkuewhsqmgbbuqcljjivswmdkqtbxixmvtrrbljptnsnfwzqfjmafadrrwsofsbcnuvqhffbsaqxwpqcac";
	string str2 = "qopubjguxhxdipfzwswybgfylqvjzhar";
	string str4 = "hchzvfrkmlnozjk";
	string str3 = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
	Solution s;
	cout << s.lengthOfLongestSubstring(str) << endl;
	cout << s.lengthOfLongestSubstring(str2) << endl;
	cout << s.lengthOfLongestSubstring(str4) << endl;
	cout << s.lengthOfLongestSubstring(str3) << endl;
	*/

	string str = "abcabc";
	Solution s;
	cout << s.lengthOfLongestSubstring(str)<<endl;
	return 0;
}
