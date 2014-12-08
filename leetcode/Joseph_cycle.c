#include <stdio.h>

int joseph(int n, int m) {

	if (!n) return 0;
	if (n == 1) return n;

	return (joseph(n-1, m) + m )%n;
}


int main() {

	int n = 10, m =5;
	printf("%d\n", joseph(n, m));
	return 0;

}

