#include <stdio.h>
#include <stdlib.h>


typedef struct _node {
	int val;
	struct _node *next;
}node;

node *create_list (void)
{
	int val;
	node *head, *p, *q;
	if (scanf("%d", &val) == 1) {
		head = (node*)malloc(sizeof(node));
		head->val = val;
	} else 
		return 0;

	q = head;

	while(scanf("%d", &val) == 1) {
		if (val < 0) break;
		p = (node*) malloc(sizeof(node));
		p->val = val;
		q->next = p;
		q = p;
	}
	
	printf("created list: \n");

	q = head;
	while(q) {
		printf("%d ", q->val);
		q=q->next;
	}
	printf("\n");

	return head;
}


node* get_intersection (const node* list1, const node* list2) {
	unsigned int num_of_list1, num_of_list2;
	unsigned int dist;
	node *p, *q;
	

	if (!list1 || !list2) 
		return 0;

	num_of_list1 = 1;
	p = list1;
	while(p->next) {
		num_of_list1++;
		p = p->next;
	}

	num_of_list2 = 1;
	q = list2;
	while(q->next) {
		num_of_list2++;
		q = q->next;
	}

	if (p != q) 
		return 0;

	
	if (num_of_list1 > num_of_list2) {
		p = list1;
		q = list2;
		dist = num_of_list1 - num_of_list2;
	} else {
		p = list2;
		q = list1;
		dist = num_of_list2 - num_of_list1;
	}

	while (dist) {
		p=p->next;
		dist--;
	}

	while (p != q) {
		p=p->next;
		q=q->next;
	}

	return p;
}

int main(int argv, char** argc) 
{
	node *list1, *list2, *list3;
	node *share_node;
	node *p;
	list1 =	create_list();
	list2 = create_list();
	list3 = create_list();
	
	p = list1;
	while(p->next) p=p->next;
	p->next = list3;

	p = list2;
	while(p->next) p=p->next;
	p->next = list3;


	share_node = get_intersection(list1, list2);

	printf("get intersection as following:\n");
	while(share_node) {
		printf("%d ", share_node->val);
		share_node = share_node->next;
	}

	return 0;

}

