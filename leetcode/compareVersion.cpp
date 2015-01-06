#include <string> 
#include <iostream>
#include <stdlib.h>
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
		int ver1, ver2;
		string str1, str2;

		if (!version1.length() && !version2.length()) return 0;
	
		int start1, start2, end1, end2;
		start1 = start2 = 0;
		do {
			ver1 = 0;  ver2 = 0;
			if (start1 > version1.length() && start2 > version2.length() )
				break;

			if (start1 < version1.length()) {
				end1 = version1.find('.', start1);
				if (-1 != end1) {
					str1 = version1.substr(start1, end1);
					start1 = end1+1;
				}
				else {
					str1 = version1.substr(start1);
					start1 = version1.length() + 1;
				}
				ver1 = atoi(str1.c_str());
			}

			if (start2 < version2.length()) {
				end2 = version2.find('.', start2);
				if (-1 != end2) {
					str2 = version2.substr(start2, end2);
					start2 = end2 + 1;
				} 
				else  {
					str2 = version2.substr(start2);
					start2 = version2.length() + 1;
				}
				ver2 = atoi(str2.c_str());
			}

			cout << "ver1 = " << ver1 << " ver2 = " << ver2 << endl;
			if(ver1 > ver2) {
				return 1;
			} else if(ver1 < ver2) {
				return -1;
			}

		} while(ver1 == ver2);

		/*
		if (-1 == end1 && -1 == end2 ) {
			str1 = version1.substr(start1);
			str2 = version2.substr(start2);
			start1 = version1.length()+1;
			start2 = version2.length()+1;
		}
		else if (-1 == end1 && -1 != end2) {
			str1 = version1.substr(start1);
			str2 = version2.substr(start2, end2);
			start1 = version1.length()+1;
			start2 = end2+1;
		}
		else if (-1 == end2 && -1 != end1)  {
			str1 = version1.substr(start1, end1);
			str2 = version2.substr(start2);
			start1 = end1+1;
			start2 = version2.length() + 1;
		}
		ver1 = atoi(str1.c_str());
		ver2 = atoi(str2.c_str());

		cout << ver1 << " " << ver2 << endl;

		if(ver1 > ver2) {
			return 1;
		} else if (ver1 < ver2) {
			return -1;
		} else if (ver1 == ver2) {
			if (start1 > version1.length() && start2 > version2.length()){
				return 0;
			} else if (start1 > version1.length() && start2 < version2.length()) {
				return -1;
			} else if (start1 < version1.length() && start2 > version2.length()) {
				return 1;
			}
		}
		*/

		return 0;
    }
};


int main() 
{
	string s1 = "0.0.1";
	string s2 = "0.1";
	string s3 = "0.0.1";
	string s4 = "0.0.1.1";
	string s5 = "0.0.1";
	string s6 = "0.0.1.0";
	Solution s; 
	cout << s.compareVersion(s1, s2) << endl;
	cout << s.compareVersion(s3, s4) << endl;
	cout << s.compareVersion(s5, s6) << endl;
	return 0;
}


