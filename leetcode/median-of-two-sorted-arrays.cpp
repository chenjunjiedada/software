#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i,j;

        int size1 = nums1.size();
        int size2 = nums2.size();

        int sum = size1 + size2;

        if (nums1.size() == 0 && nums2.size() == 0)
            return 0;

        if (size1 == 0)
        {
            if (size2%2) 
                return nums2[(size2-1)/2];
            else 
                return ((double)nums2[size2/2] + (double)nums2[(size2-1)/2])/2;
        }

        if (size2 == 0) 
        {
            if (size1%2) 
                return nums1[(size1-1)/2];
            else 
                return ((double)nums1[size1/2] + (double)nums1[(size1-1)/2])/2;
        }

       
        i = 0; j = 0;

        if (sum%2) {
            while ( (i+j) != sum/2 && i < size1 && j < size2) 
            {
                if (nums1[i] <= nums2[j]) 
                    i++;
                else 
                    j++;
            }

            if ( i == size1)
                return nums2[sum/2 - size1];
            else if ( j == size2)
                return nums1[sum/2 - size2];
            else if ((i+j) == sum/2) 
            {
                return  nums1[i] < nums2[j] ? nums1[i]:nums2[j];
            }
            
        }

        if (sum%2 == 0) 
        {
            while ( (i+j) != (sum/2-1) && i < size1 && j < size2) 
            {
                if (nums1[i] <= nums2[j]) 
                    i++;
                else 
                    j++;
            }

            if ( i == size1) 
                return ((double)nums2[sum/2 - size1 - 1] + (double)nums2[sum/2 - size1])/2;
            else if (j == size2)
                return ((double)nums1[sum/2 - size2 - 1] + (double)nums1[sum/2 - size2])/2;
            else if ((i+j) == (sum/2-1)) 
                return ((double)nums1[i] + (double)nums2[j]) /2;

        }
    }
};


int main(int argc,  char* argv[]) 
{
    Solution s;
    std::vector<double> nums1;
    std::vector<double> nums2;

    nums1.push_back(1);
    nums1.push_back(5);
    nums1.push_back(6);
    nums2.push_back(2);
    nums2.push_back(4);
    nums2.push_back(7);

    double a;
    a = s.findMedianSortedArrays(nums1, nums2);
    std::cout << a << std::endl;

    return 0;

}
