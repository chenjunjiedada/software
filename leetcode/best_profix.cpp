#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int buy, sell, flag;
		int i;
		int profit = 0;
		if (prices.size() == 0) return 0;
		buy = sell =  prices[0];
		flag = 0;
		for (i=1; i<prices.size(); i++) {
			if (prices[i] > sell) {
				flag = 0;
				sell = prices[i];
			} else {
				if (flag) {
					sell = prices[i];
				}
			}

			if (sell - buy > 0) {
				flag = 0;
				if(profit < sell - buy)
					profit = sell - buy;
			}

			if (prices[i] < buy) {
				buy = prices[i];
				flag = 1;
			}
		}

		return profit;
    }
};


int main() {
vector<int> a;
a.push_back(1);
a.push_back(2);

Solution s;


printf("%d\n", s.maxProfit(a));

return 0;



}
