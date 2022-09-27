 ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head=nullptr;
        ListNode* temp=nullptr;
        int left=0;
        int total=0;
        int num_1,num_2;
        while(l1||l2)
        {
            num_1=l1?l1->val:0;
            num_2=l2?l2->val:0;
            total=num_1+num_2+left;
            if(!head)
            {
                head=temp=new ListNode(total%10);
            }
            else
            {
                temp->next=new ListNode(total%10);
                temp=temp->next;
            }
            left=(total>=10)?1:0;
            if(l1) l1=l1->next;
            if(l2) l2=l2->next;
        }
        if(left) temp->next=new ListNode(left);
        return head;
    }
