
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    int carry = 0;
    ListNode l3 = ListNode(-1);
    ListNode *p3 = &l3;

    // shared digits
    while (l1 != nullptr && l2 != nullptr) {
        int sum = l1->val + l2->val + carry;
        p3->next = new ListNode(sum % 10);
        carry = sum / 10;

        p3 = p3->next, l1 = l1->next, l2 = l2->next;
    }
	
    // remaining digits
    l1 = (l1 == nullptr) ? l2 : l1;
    while (l1 != nullptr) {
        int sum = l1->val + carry;
        p3->next = new ListNode(sum % 10);
        carry = sum / 10;

        p3 = p3->next, l1 = l1->next;
    }

    // one carry-over
    if (carry == 1)
        p3->next = new ListNode(1);

    return l3.next;
}
