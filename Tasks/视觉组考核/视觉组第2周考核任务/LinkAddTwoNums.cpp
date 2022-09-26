
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head=new ListNode();
        ListNode* ret=head;
        int carry=0;
        int num=0;
        while(l1!=nullptr&&l2!=nullptr){
            num=l1->val+l2->val+carry;
            carry=0;
            if(num>9){
                carry=1;
                num-=10;
            }
            ret->next=new ListNode(num);
            ret=ret->next;
            l1=l1->next;
            l2=l2->next;
        }
        if(l1!=nullptr){
            ret->next=l1;
        }
        else if(l2!=nullptr){
            ret->next=l2;
        }
        while(carry){
                carry=0;
                if(ret->next==nullptr){
                    ret->next=new ListNode(1);
                }
                else if(++(ret->next->val)>9){
                    ret->next->val=0;
                    carry=1;
                }
                ret=ret->next;
            }
        return head->next;
    }
};

