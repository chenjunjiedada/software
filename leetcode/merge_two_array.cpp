#include <iostream>

using namespace std;

class Solution {
	public:
		void merge(int a[], int m, int b[], int n) {
			int i, j;
			int t;

			if (!n) return; 

			i=0;
			while(i<m) {
				a[m+n-i-1] = a[m-1-i] ;
				i++;
			}

			i = n; j = 0; t = 0;
			while(i<m+n && j<n){
				if(a[i] < b[j]) 
					a[t++] = a[i++];
				else 
					a[t++] = b[j++];
			}

			if(i==m+n) {
				while(j<n) {
					a[t++] = b[j++];
				}
			} else if(j==n){
				while(i<m+n-1){
					a[t++] = a[i++];
				}
			}
		}
};



int main()
{
	int i;
	int a[] = {1, 5, 7, 9, 0, 0, 0, 0};
	int b[] = {4, 6, 10};

	Solution s;

	s.merge(a, 4, b, 3);


	for (i=0; i<8; i++) {
		cout << a[i] << " ";
	}

	cout << endl;

	return 0;
}
