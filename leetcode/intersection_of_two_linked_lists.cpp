#include <stdio.h>
#include <stdlib.h>

/**
 *  * Definition for singly-linked list.
 *    struct ListNode {
 *        int val;
 *        ListNode *next;
 *        ListNode(int x) : val(x), next(NULL) {}
 *    };
 */

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL) {}
};

class Solution {
	public:
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
			unsigned int num_of_list1, num_of_list2;
			unsigned int dist;
			struct ListNode *p, *q;
			struct ListNode *list1, *list2;
			list1 = headA;
			list2 = headB;

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

			return (struct ListNode*) p;
		}
};

struct ListNode *create_list (void)
{
	int val;
	struct ListNode *head, *p, *q;
	if (scanf("%d", &val) == 1) {
		head = (struct ListNode *)malloc(sizeof(struct ListNode));
		head->val = val;
	} else 
		return 0;

	q = head;

	printf("creating list: \n");
	while(scanf("%d", &val) == 1) {
		if (val < 0) break;
		p = (struct ListNode *)malloc(sizeof(struct ListNode));
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

int main(int argv, char** argc) 
{
	struct ListNode *list1, *list2, *list3;
	struct ListNode *share_node;
	struct ListNode *p;
	list1 =	create_list();
	list2 = create_list();
	list3 = create_list();

	Solution s;
	
	
	p = list1;
	while(p->next) p=p->next;
	p->next = list3;

	p = list2;
	while(p->next) p=p->next;
	p->next = list3;


	share_node =s.getIntersectionNode(list1, list2);

	printf("get intersection as following:\n");
	while(share_node) {
		printf("%d ", share_node->val);
		share_node = share_node->next;
	}

	return 0;

}

