/*************************************************************************
	> File Name: List.cpp
	> Author: zxq
	> Mail: 1459190705@qq.com
	> Created Time: Fri 11 Mar 2022 03:55:05 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


struct ListNode {
    int val;
    ListNode* next;
    ListNode():val(0), next(nullptr){}
    ListNode(int val): val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(next){}
};

ostream &operator<<(ostream &out, const ListNode *head) {
    while (head) {
        out << head->val << " ";
        head = head->next;
    }
    return out;
}


void merge(ListNode* &p1, ListNode* &p2) {
    ListNode ret, *head = &ret;
    while(p1 || p2) {
        if (p2 == nullptr || (p1 && p1->val < p2->val)) {
            head->next = p1;
            p1 = p1->next;
        } else {
            head->next = p2;
            p2 = p2->next;
        }
        head = head->next;
    }
    p1 = ret.next;
    p2 = nullptr;
    return ;
}
/*
void merge(ListNode* &L1, ListNode* &L2) 
{
    if (L2 == nullptr) return ;
    ListNode* p2 = L2;
    ListNode ret(0), *p = &ret;
    p->next = L1;
    while (p->next && p2) {
        if (p->next->val > p2->val) {
            ListNode *next = p2->next;
            p2->next = p->next;
            p->next = p2;
            p2 = next;
            p = p->next;
        } else {
            p = p->next;
        }
    }
    if (p2) {
        p->next = p2;
    }
    L2 = nullptr;
    L1 = ret.next;
    return;
}
*/

ListNode* Listsort(ListNode* head) 
{
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* carry, *counter[64];
    int fill = 0;
    while (head) {
        carry = head;
        head = head->next;
        carry->next = nullptr;
        int i = 0;
        for ( ;i < fill && counter[i]; i++) {
            merge(carry, counter[i]); //将counter[i]合并到carry
        }
        swap(carry, counter[i]);
        if (i == fill) ++fill;
    }
    for (int i = 1; i < fill; i++) merge(counter[i], counter[i - 1]);
    return counter[fill - 1];
}



int main() {
    int n;
    cin >> n;
    ListNode *head = new ListNode(), *p = head;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        p->next = new ListNode(a);
        p = p->next;
    }
    cout << head->next << endl;
    head->next = Listsort(head->next);
    cout << head->next << endl;
    return 0;
}





