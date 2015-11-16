//Given a string S, find the longest palindromic substring in S. 
//You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
       int i, j, k, max_len;
       if (s.size() < 2) return s;

       string lp = s.substr(0, 1);
       int r = 0;
       i = 1;
       max_len = 1;

       while ( i < s.length() ) {
           int len1 = 0;
           int len2 = 1;
           
           if (i<max_len/2 || (s.length() -i )< max_len/2) {
               i++;
               continue;
           }

           for(j=i-1, k = i; j >= 0 && k < s.length(); j--, k++) {
               if (s[j] == s[k])
                   len1 += 2;
               else 
                   break;
           }

           for(j=i-1, k = i+1; j >= 0 && k < s.length(); j--, k++) {
               if (s[j] == s[k])
                   len2 += 2;
               else 
                   break;
           }

           len1 = len1 > len2 ? len1:len2;

           if (len1 > max_len) {
                max_len = len1;
                r = i;
           }
           i++;
       }

       lp = s.substr(r-max_len/2, max_len);
       return lp; 
    }
};


int main() {
    std::string str;
    std::cin >> str;
    Solution s;
    std::cout << s.longestPalindrome(str) << std::endl;
    return 0;
}
