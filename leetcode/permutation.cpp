#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
	Solution() {
		offset = 0;
	}

public:
	void swap(vector<int> &num, int i, int j) {
		int tmp;
		tmp = num[i];
		num[i] = num[j];
		num[j] = tmp;
	}

public:
	int offset;
    vector<vector<int> > an;
    
public:
    vector<vector<int> > permute(vector<int> &num) {
		int i;

		if (!num.size()) return an;

        if (offset == num.size()-1) {
			an.push_back(num);
			return an;
        }

		for (i = offset; i < num.size(); i++) {
			swap(num, offset, i);
			offset ++;
			permute(num);
			offset --;
			swap(num, offset, i);
		}
		return an;
    }

};

int main() {
	vector<vector<int> > bn;
	Solution s;
	vector<int> num;
	num.push_back(1);
	num.push_back(2);
//	num.push_back(3);
//	num.push_back(4);

	bn = s.permute(num);

	for(int i = 0; i<bn.size();i++) {
		for(int j = 0; j<bn[i].size(); j++) {
			cout << bn[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
