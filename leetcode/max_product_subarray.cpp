#include <stdio.h>

class Solution {
	public:
		int maxProduct(int A[], int n) {
			int maxPro=A[0];
			int i = 0;
			int res = A[0];
			int nres = 1;
			for (i = 1; i< n; i++) {
				if (!res) {
					maxPro = A[i] > maxPro ? A[i]: maxPro;
					res = A[i];
					nres = 1;
				}
				else if (res > 0) {
					res *= A[i];
					maxPro = res > maxPro ? res : maxPro;
				}
				else if (res < 0) {
					/* 2 5 -2 -4 -3  2 */
					if (nres > 0)
					 	nres = res;
					res *= A[i];

					if (res < A[i]) maxPro = A[i] > maxPro ? A[i]: maxPro;
					else 
						maxPro = res > maxPro ? res : maxPro;

				}

				if (maxPro < res/nres) {
					maxPro = res/nres;
				}


			}

			return maxPro;
		}
};


int main() {
	Solution s;
	int a[] = {2, 3, -4, 5};
	int b[] = {2, 3, -4, 1, -2};
	int c[] = {0, 2};
	int d[] = {2, 0};
	int e[] = {2, -1, 3};
	int f[] = {1,0,-1,2,3,-5,-2};
	int g[] = {2, -5, -2, -4, 3};


	printf("%d\n", s.maxProduct(a, 4));
	printf("%d\n", s.maxProduct(b, 5));
	printf("%d\n", s.maxProduct(c, 2));
	printf("%d\n", s.maxProduct(d, 2));
	printf("%d\n", s.maxProduct(e, 3));
	printf("%d\n", s.maxProduct(f, 7));
	printf("%d\n", s.maxProduct(g, 5));

	return 0;

}
