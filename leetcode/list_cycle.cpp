#include <stdio.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
    ListNode* hasCycle(ListNode *head) {
        if (!head) 
			return 0;
        ListNode *p = head;
        ListNode *q = head->next;
        
        while(p && q){
            if(p==q) 
                return p;
            p = p->next;
            q = q->next;
            
            if(q){
                q = q->next;
            }
        }
        return 0;
    }

	ListNode* firstNode(ListNode *head) {
		int num_of_cycle = 0;	
		if (!head) 
			return 0;

		ListNode *p = hasCycle(head);
		if (!p) 
			return 0;

		ListNode *q = p;
	
		do{
			p=p->next;
			num_of_cycle ++;
		} while(p != q);

		q = p = head;

		while (num_of_cycle--) q = q->next;

		while (p != q) {p=p->next;q=q->next;}
		return p;
	}
};


int main() {
	ListNode p1(1);
	ListNode p2(2);
	ListNode p3(3);
	ListNode p4(4);
	ListNode p5(5);
	ListNode p6(6);
	ListNode p7(7);
	ListNode p8(8);
	p1.next = &p2; 
	p2.next = &p3; 
	p3.next = &p4; 
	p4.next = &p5; 
	p5.next = &p6; 
	p6.next = &p7;
	p7.next = &p8;
	p8.next = &p5;

	Solution s;
	ListNode *p = s.firstNode(&p1);

	printf("%d\n", p->val);

	return 0;
}
