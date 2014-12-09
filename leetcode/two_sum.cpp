#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int i = 0, index;
        map<int, int> m;
        vector<int> answer;

		/* 
		 * assume target = a + b;
		 * travese array a one by one, 
		 * check whether there is a solution (b->a.index) in map
		 * if not, store wanted solution to map. 
		 * if yes, we got a real b, push m[b] which is a.index, and current b.index
		 */
        for (i = 0; i < numbers.size(); i++) {
			if (m.find(numbers[i]) == m.end())
				m[target - numbers[i]] = i;
			else {
				answer.push_back(m[numbers[i]] + 1);
				answer.push_back(i+1);
				break;
			}
		}
        
        return answer;
    }
};

int main() {
	vector<int> arr; 
	vector<int> ans;
	arr.push_back(0);
	arr.push_back(3);
	arr.push_back(4);
	arr.push_back(0);


	Solution s;
	ans = s.twoSum(arr, 0);


	for(int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}

	cout << endl;

	return 0;
}
