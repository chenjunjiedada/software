#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int buy, sell, i;
		int profit = 0;
		buy = sell =  prices[0];

		i = 1;
		while(i < prices.size()) {
			if (prices[i] > sell) {
				sell = prices[i];
				if (sell - buy > profit) 
					profit = sell - buy;
			}

			if (prices[i] < buy) {
				buy = prices[i];
				sell = prices[i];
			}
			i++;
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
