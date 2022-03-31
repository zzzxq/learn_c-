/*************************************************************************
	> File Name: Bucket_sort.cpp
	> Author: zxq
	> Mail: 1459190705@qq.com
	> Created Time: Thu 31 Mar 2022 11:33:17 AM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;


struct ListNode {
    double key;
    ListNode *next;
    ListNode() {}
    ListNode(double key) : key(key) {}
};

void bucket_sort(double *first, double *last, int bucket_size)
{
    vector<ListNode> Bucket(bucket_size);
    double *temp = first;
    while (temp != last) {
        int index = *temp * 10;
        ListNode *p = new ListNode(*temp);
        ListNode *q = &Bucket[index];
        while (q->next && q->next->key < *temp) q = q->next;
        p->next = q->next;
        q->next = p;
        ++temp;
    }
    temp = first;
    for (int i = 0; i < bucket_size; i++) {
        ListNode *p = &Bucket[i];
        while (p->next) {
            *temp = p->next->key;
            p = p->next;
            ++temp;
        }
    }

}

int main() 
{
    double arr[20] = {0.65, 0.008, 0.0576, 0.1234, 0.432, 0.65464, 0.7786, 0.567567, 0.1, 0.2, 0.899, 0.25, 0.37, 0.42, 0.48, 0.19, 0.28, 0.39, 0.89, 0.97};
    bucket_sort(arr, arr + 20, 10);
    for (int i = 0; i < 20; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


