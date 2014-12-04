#include <stdio.h>
class Solution {
	public:
		int singleNumber(int A[], int n) {
			int i;
			for (i=1; i<n; i++) {
				A[0] =A[0] ^ A[i];
			}	
			return A[0];

		}
};


int main() {
	Solution s;

	int a[] = {1, 2, 3, 4, 5, 1, 2, 3, 4};
	
	printf("%d\n", s.singleNumber(a, 9));
	return 0;



}
