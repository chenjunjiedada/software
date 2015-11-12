#include <iostream>
#include <vector>
#include <cmath>


std::vector<int> findtwomax(std::vector<char> &nums) 
{
    int i = 0;
    int max = nums[0];
    int submax = nums[1];

    std::vector<int> idx;
    idx.push_back(0);
    idx.push_back(1);

    
    for (i = 1; i<nums.size(); i++) 
    {
        if (nums[i] > max) 
        {
            submax = max;
            max = nums[i];
            idx[0] = idx[1];
            idx[1] = i;     
        }
        else if (nums[i] > submax) 
        {
            submax = nums[i];
            idx[0] = i;
        }
    }

    return idx;
}

std::vector<int> findtwomin(std::vector<char> &nums) 
{
    int i = 0;
    int min = nums[0];
    int submin = nums[1];

    std::vector<int> idx;
    idx.push_back(0);
    idx.push_back(1);

    
    for (i = 1; i<nums.size(); i++) 
    {
        if (nums[i] < min) 
        {
            submin = min;
            min = nums[i];
            idx[1] = idx[0];
            idx[0] = i;     
        }
        else if (nums[i] < submin) 
        {
            submin = nums[i];
            idx[1] = i;
        }
    }

    return idx;
}


std::vector<int> get_max_product(std::vector<char> &nums) 
{
    std::vector<int> min = findtwomin(nums);
    std::cout << "two min:" << (int)nums[min[0]] << "  " << (int)nums[min[1]] << std::endl;

    std::vector<int> max = findtwomax(nums);
    std::cout << "two max:" << (int)nums[max[0]] << "  " << (int)nums[max[1]] << std::endl;

    double min1 = std::abs(nums[min[0]]);
    double min2 = std::abs(nums[min[1]]);
    double max1 = std::abs(nums[max[0]]);
    double max2 = std::abs(nums[max[1]]);


    if (min1/max1 < max2/min2)
    {
        return max;
    }
    else
    {
        return min;
    }
}

int main() 
{
    std::vector<char> nums;
    nums.push_back(-127);
    nums.push_back(-100);
    nums.push_back(-2);
    nums.push_back(3);
    nums.push_back(127);
    nums.push_back(23);

    std::vector<int> a = get_max_product(nums);

    std::cout << (int)nums[a[0]] << " * " << (int)nums[a[1]] << std::endl;

}
