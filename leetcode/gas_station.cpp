#include <vector> 
#include <iostream>

using namespace std;

class Solution
{
	public: 
		int canCompleteCircuit(vector<int> &gas, vector<int>& cost)
    {
        int previous = 0;
        int index = 0;
        int restGas = 0;
        for (int i = 0; i < gas.size(); ++i)
        {
            restGas += gas[i] - cost[i];

            if (restGas < 0)
            {
                previous += restGas;
                restGas = 0;
                index = i + 1;
            }
        }

        if (restGas + previous >= 0)
        {
            return index;
        }
        else
        {
            return -1;
        }
    }
};


int main() 
{
	vector<int> gas;
	vector<int> cost;
	gas.push_back(1);
	gas.push_back(2);
	gas.push_back(3);

	cost.push_back(3);
	cost.push_back(2);
	cost.push_back(1);

	Solution s;
	cout << gas[0] << " " << gas[1] << " " << gas[2] << endl;
	cout << cost[0] << " " << cost[1] << " " << gas[2] <<endl;
	cout <<s.canCompleteCircuit(gas, cost) << endl;
	return 0;


}
