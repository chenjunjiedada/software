#include <stdio.h>
class Solution {
	public:
		int singleNumber(int A[], int n) {
			int result = 0;

			int x, sum;

			// Iterate through every bit
			for (int i = 0; i < 32; i++)
			{
				// Find sum of set bits at ith position in all
				// array elements
				sum = 0;
				x = (1 << i);
				for (int j=0; j< n; j++ )
				{
					if (A[j] & x)
						sum++;
				}

				// The bits with sum not multiple of 3, are the
				// bits of element with single occurrence.
				if (sum % 3)
					result |= x;
			}

			return result;	
		}
};

int main() {
	int a[] = {2, 3, 3, 2, 3, 2, 4};
	Solution s;
	printf("%d\n", s.singleNumber(a, 7));
	return 0;

}
