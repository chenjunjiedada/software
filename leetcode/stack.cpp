#include <stdlib.h>
#include <stdio.h>

class MinStack {
	public: 
		int minIndex;
		int *stack;
		int *min_index;
		int size_of_stack;
		int index;
		MinStack(){
			stack = 0;
			index = -1;
			min_index = 0;
			size_of_stack = 1024;
			minIndex = 0;
		}
	
	public:
		void push(int x) {
			if (!stack) {
				stack = (int *)malloc(sizeof(int) * size_of_stack);
				min_index = (int *)malloc(sizeof(int) * size_of_stack);
				stack[++index] = x;	
				min_index[0] = minIndex;
				return ;
			}

			if (index+1 == size_of_stack) {
				stack = (int *)realloc(stack, sizeof(int) * size_of_stack * 2);
				min_index = (int *)realloc(min_index, sizeof(int) * size_of_stack *2);
				size_of_stack = size_of_stack << 1;
			} 

			stack[++index] = x;

			if (stack[minIndex] > x ) {
				min_index[index] = minIndex;
				minIndex = index;
			} 

			return ;
		}

		void pop() {
			if (!stack || index < 0) 
				return ;

			if (index == minIndex) {
				minIndex = min_index[index];
			}

			index--;
		}

		int top() {
			if (!stack || index < 0) 
				return 0;

			return stack[index];
		} 

		int getMin() {
			if (!stack || index < 0) 
				return 0;
			return stack[minIndex];
		}
};

void show(int *a, int len) {
	int i = 0;
	printf ("stack len: %d\n", len);
	while(i <= len) {
		printf("%d\t", a[i]);
		i++;
	}
	printf("\n");
}


int main(int argc, char ** argv) {

	int i = 0;
	int j = 0;
	MinStack mstack;	

	/*
	while(j<10000) {
		mstack.push(-10000 + j++);
	}
	*/

	mstack.push(6);
	mstack.push(4);
	mstack.push(11);
	mstack.push(5);
	mstack.push(3);
	mstack.push(7);
	mstack.push(8);
	mstack.push(10);
	mstack.push(9);
	mstack.push(1);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);
	
	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	mstack.pop();
	show(mstack.stack, mstack.index);
	printf("min : %d index = %d \n", mstack.getMin(), mstack.index);

	return 0;
}
