#include <stdio.h>

class Solution {
	public:
		int maxProduct(int A[], int n) {
			int maxSum=A[0];
			int i = 0;
			int res = A[0];
			for (i = 1; i< n; i++) {
				if(res < 0) {
					res = A[i];
					if (maxSum < res) 
						maxSum = res;
				} else {
					res += A[i];
					if (res > maxSum) 
						maxSum = res;
				}

			}

			return maxSum;
		}
};


int main() {
	Solution s;
	int a[] = {2, 1, -4, 4, 5};
	int b[] = {2, 3, -4, 5, 4};
	int c[] = {-2, -4};
	int d[] = {-4, -2};

	printf("%d\n", s.maxProduct(a, 5));
	printf("%d\n", s.maxProduct(b, 5));
	printf("%d\n", s.maxProduct(c, 2));
	printf("%d\n", s.maxProduct(d, 2));
	return 0;

}
