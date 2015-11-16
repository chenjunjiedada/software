#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
    public:
        std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
            int i, j, k;

            std::vector<std::vector<int>> r;

            int size = nums.size();

            for (i = 0; i < (size - 2); i++) {
                int t = 0 - nums[i];
                std::vector<int> tmp;
                for (j = i+1, k = size - 1; j < k ; ) {
                    if ( (nums[j] + nums[k]) == t) 
                    {
                        tmp.push_back(nums[i]);
                        tmp.push_back(nums[j]);
                        tmp.push_back(nums[k]);
                        r.push_back(tmp);
                    }
                    if ( (nums[j] + nums[k]) < t ) j++;
                    else  k--;
                }
            }
            
            return r;
        }
};

int main () {

    std::vector<int> nums;
    nums.push_back(-2);
    nums.push_back(-3);
    nums.push_back(-4);
    nums.push_back(-0);
    nums.push_back(2);
    nums.push_back(5);
    nums.push_back(6);

    std::sort(nums.begin(), nums.end());

    for(auto i = nums.begin(); i!=nums.end(); i++) {
        std::cout << *i << std::endl;
    }

    std::vector<std::vector<int>> a;
    Solution s;

    a = s.threeSum(nums);


    for(auto i = a.begin(); i!=a.end(); i++) {
        std::vector<int> tmp = *i;
        std::cout << tmp[0] << " + " << tmp[1] << " + " << tmp[2] <<std::endl;
    }
    
    return 0;
}
