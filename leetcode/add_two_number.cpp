/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int val;
    ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void showList(struct ListNode * h) {
	while(h){
		printf("%d ", h->val);
		h = h->next;
	}
	printf("\n");
}



class Solution {
    public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
	    int carry;
	    struct ListNode *r = new ListNode(0);
	    struct ListNode *head = r;

		carry = 0;
		while(l1 && l2) {
			r->next = new ListNode((l1->val + l2->val + carry)%10);
			carry = (l1->val + l2->val + carry)/10;
			l1 = l1->next;
			l2 = l2->next;
			r = r->next;
		}

		showList(head);

	    if (l2) l1 = l2;	

		while(l1) {
			r->next = new ListNode((l1->val + carry)%10);
			carry = (carry + l1->val)/10;
			l1 = l1->next;
			r = r->next;
		}

		if (carry) {
			r->next = new ListNode(carry);
		}

		r = head;
		head = head->next;
		free(r);

		return head;
	}
};

struct ListNode *initList(int a[], int len) {
    int i = 0;
    struct ListNode *head, *p, *q;
    head = 0;

    while (i < len) {
	q = (struct ListNode *)malloc(sizeof(struct ListNode ));
	q->val = a[i];
	if (!head){
	    head = q;
	    p = q;
	}
	else {
	    p->next = q;
	    p = p->next;
	}
	i++;
    }
    return head;

}
int main() {

    int a[] = {0};
    int b[] = {2, 7, 8};
    struct ListNode *la, *lb, *lc;

    la = initList(a, 1);
    lb = initList(b, 3);

	showList(la);
	showList(lb);

	Solution s;
	lc = s.addTwoNumbers(la, lb);

	showList(lc);
	return 0;

}


