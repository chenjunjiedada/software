#include <limits.h>
#include <iostream>
using namespace std;


int reverseint(int x)
{
	int y = 0;
	while(x) {
		if (y>0 && y > INT_MAX/10) return 0;
		if (y<0 && y < INT_MIN/10) return 0;
		y *= 10;

		if (y>0 && y > INT_MAX - x%10) return 0;
		if (y<0 && y < INT_MIN - x%10) return 0;
		y += x%10;
		x /= 10;
	}
	return y;
}

int main() 
{
	cout << reverseint(1534236469)<< endl;
	cout << reverseint(-123)<< endl;
	cout << reverseint(153423641)<< endl;
	return 0;

}
