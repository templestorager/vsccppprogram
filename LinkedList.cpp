#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void printList( ListNode *head )
{
    if ( !head )
        cout << "Empty list " << endl;
    while( head->next )
    {
        cout << head->val << "->";
        head = head->next;
    }
    cout << head->val << endl;
}

ListNode *reverseList(ListNode *head )
{
    ListNode dummyhead = ListNode(-1);
    if ( !head ) 
        return head;
    while( head )
    {
        ListNode *next = head->next;
        head->next = dummyhead.next;
        dummyhead.next = head;
        head = next;
    }     
    return dummyhead.next; 
}

ListNode* plusOne(ListNode* head) 
{
    if ( !head )
        return head;
    ListNode *reverse_head = reverseList(head), *walk = reverse_head, *tail;
    int carry = 1;
    while(walk)
    {
        int sum = walk->val + carry;
        if ( sum < 10 )
        {
            walk->val = sum;
            carry = 0;
            break;
        }
        else
        {
            walk->val = sum % 10;
            carry = sum / 10;
        }
        tail = walk;
        walk = walk->next;
    }
    
    if ( carry )
    {
        ListNode *lastnode = new ListNode(carry);
        tail->next = lastnode;
    }
    return reverseList(reverse_head);
}

ListNode* plusOneStack(ListNode* head) 
{
    stack<ListNode*> s;
    if ( !head ) 
        return head;
    ListNode *walk = head;
    while( walk )
    {
        s.push(walk);
        walk = walk->next;
    }
    
    int sum = 0, carry = 1;
    while ( !s.empty() && carry )
    {
        ListNode *top = s.top();
        s.pop();
        sum = top->val + carry;
        top->val = sum % 10;
        carry = sum / 10;
    }
    
    if ( carry )
    {
        ListNode *last_carry = new ListNode(carry);
        last_carry->next = head;
        head = last_carry;
    }
    
    return head;
}

int main()
{
    ListNode head(9);
    vector<int> data{1,2,3};
    ListNode *res = plusOne(&head);
    printList(res);
    ListNode dummy(0), *tail = &dummy;
    for ( int i = 0; i < data.size(); i++ )
    {
        ListNode *tmp = new ListNode(data[i]);
        tail->next = tmp;
        tail = tmp;
    }
    printList(dummy.next);
    plusOneStack( dummy.next );
    printList(dummy.next);
}