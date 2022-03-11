/*************************************************************************
	> File Name: sort.cpp
	> Author: zxq
	> Mail: 1459190705@qq.com
	> Created Time: Fri 11 Mar 2022 08:46:28 AM CST
 ************************************************************************/

#include<iostream>
#include<functional>
#include<vector>
using namespace std;


const int threthold = 5;

int get_Mid(int a, int b, int c) 
{
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    return b;
}


class RandomIterator
{
public:
    RandomIterator(int *a) : p(a) {}
    RandomIterator(const RandomIterator &r) {
        p = r.p;
    }
    RandomIterator &operator=(const RandomIterator &r) {
        p = r.p;
        return *this;
    }
    int &operator*() const { return *p; }
    RandomIterator operator+(int n) const {
        return RandomIterator(p + n);
    }
    RandomIterator operator-(int n) const {
        return RandomIterator(p - n);
    }
    int operator-(const RandomIterator &r) {
        return p - r.p;
    }
    RandomIterator &operator++() {
        ++p;
        return *this;
    }
    RandomIterator &operator--() {
        --p;
        return *this;
    }
    RandomIterator operator++(int) {
        RandomIterator temp = *this;
        ++p;
        return temp;
    }
    RandomIterator operator--(int) {
        RandomIterator temp = *this;
        --p;
        return temp;
    }
    bool operator<(const RandomIterator &iter) const {
        return p < iter.p;
    }
    bool operator>(const RandomIterator &iter) const {
        return iter < *this;
    }
    bool operator<=(const RandomIterator &iter) const {
        return !(*this > iter);
    }
    bool operator>=(const RandomIterator &iter) const {
        return !(*this < iter);
    }
    bool operator==(const RandomIterator &iter) const {
        return !(*this > iter) && !(*this < iter);
    }
    bool operator!=(const RandomIterator &iter) const {
        return !(*this == iter);
    }
    
private:
    int *p;
};


void intro_sort(RandomIterator first, RandomIterator last, function<bool(int, int)> cmp = less<int>()) 
{
    while (last - first > threthold) {
        RandomIterator x = first, y = last - 1;
        int pivot = get_Mid(*first, *(last - 1), *(first + (last - first) / 2));
        while (x <= y) {
            while (cmp(*x, pivot)) x++;
            while (cmp(pivot, *y)) y--;
            if (x <= y) {
                swap(*x, *y);
                x++, y--;
            }
        }
        intro_sort(x, last);
        last = y + 1;
    }   
    return;
}

void insertion_sort(RandomIterator first, RandomIterator last, function<bool(int, int)> cmp = less<int>()) 
{
    RandomIterator ind = first;
    for (RandomIterator j = first; j < last; j++) {
        if (cmp(*j, *ind)) ind = j;
    }
    for (RandomIterator j = ind; j > first; j--) {
        swap(*j, *(j - 1));
    }
    for (RandomIterator j = first + 2; j < last; j++) {
        ind = j;
        while (cmp(*ind, *(ind - 1))) {
            swap(*ind, *(ind - 1));
            ind--;
        }
    }
    return;
}


void sort(RandomIterator first, RandomIterator last, function<bool(int, int)> cmp = less<int>()) 
{
    intro_sort(first, last, cmp);
    insertion_sort(first, last, cmp);
    return;
}



int main() {
    int n;
    int a[100];
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n, less<int>());
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}


