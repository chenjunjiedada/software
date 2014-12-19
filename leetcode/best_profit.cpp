#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
		int buy, sell, i;
		int profit = 0, sum = 0;

		if (prices.size() == 0) return 0;

		buy = sell =  prices[0];

		i = 1;
		while(i < prices.size()) {
			if (prices[i] > sell) {
				sell = prices[i];
				if (sell - buy > profit) {
					profit = sell - buy;
				}
			}

			if (prices[i] < sell) {
				sum += profit;
				cout << profit << endl;
				profit = 0;
				buy = prices[i];
				sell = prices[i];
			}


			i++;
		}
		sum += profit;

		return sum;
    }
};


int main() {
vector<int> a;
a.push_back(6);
a.push_back(1);
a.push_back(3);
a.push_back(2);
a.push_back(4);
a.push_back(7);

Solution s;


printf("%d\n", s.maxProfit(a));

return 0;



}
