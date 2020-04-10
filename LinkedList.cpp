#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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

int CountList( ListNode * head) 
{
    int cnt = 0;
    while( head )
    {
        cnt++;
        head = head->next;
    }
    return cnt;
}

ListNode * reverseList2( ListNode *head )
{
    ListNode dummy(-1);
    while( head )
    {
        ListNode *next = head->next;
        head->next = dummy.next;
        dummy.next = head;
        head = next;
    }
    
    return dummy.next;
}

void reorderList(ListNode* head) {
    if ( !head || !head->next )
    return;
    ListNode *left, *right, *tail, *prev;
    int n = CountList(head);
    left = tail = head;
    for(int i = 0; i < (n+1) / 2; i++ )
    {
        prev = tail;
        tail = tail->next;
    }
    right = tail;
    prev->next = NULL;
    right = reverseList(right);
    while( left && right )
    {
        ListNode *tmp = right->next;
        right->next = left->next;
        left->next = right;
        right = tmp;
        left = left->next->next;
    }

}

ListNode *ConstructList( const vector<int>& data )
{
    ListNode dummy(0), *tail = &dummy;
    for ( int i = 0; i < data.size(); i++ )
    {
        ListNode *tmp = new ListNode(data[i]);
        tail->next = tmp;
        tail = tmp;
    }
    return dummy.next;
}

void reorderList2(ListNode* head) {
    queue<ListNode*> q;
    stack<ListNode *> s;
    ListNode *walk = head;
    ListNode dummyhead(-1), *tail = &dummyhead;
    while ( walk && walk->next )
    {
        q.push(walk);
        s.push(walk->next);
        walk = walk->next->next;
    }
    if ( walk )
        q.push(walk);
    q.back()->next = NULL;
    // merge the queue and stack 
    while ( !q.empty() && !s.empty() )
    {
        ListNode *qnode = q.front();
        q.pop();
        tail->next = qnode;
        ListNode *snode = s.top();
        s.pop();
        snode->next = qnode->next;
        qnode->next = snode;
        tail = snode;
    }
    head = dummyhead.next;
}

int main()
{
    ListNode head(9);
    vector<int> data{1,2,3,4};
    ListNode *res = plusOne(&head);
    printList(res);
    ListNode *list = ConstructList(data);
    printList(list);
    plusOneStack( list );
    printList(list);
    ListNode *list3 = ConstructList(data);
    reorderList2(list3);
    printList(list3);
}