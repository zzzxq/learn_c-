/*************************************************************************
	> File Name: Queue.cpp
	> Author: zxq
	> Mail: 1459190705@qq.com
	> Created Time: Fri 11 Mar 2022 04:20:55 PM CST
 ************************************************************************/

#include<iostream>
#include<functional>
using namespace std;



class IQueue {
public:
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual bool empty() const = 0;
    virtual int top() const = 0;
    virtual int size() const = 0;
};


class my_priority_queue : public IQueue {
public:
    typedef function<bool(int, int)> CMP_T;
    my_priority_queue(int n = 10, CMP_T cmp = less<int>()) : rawdata(new int[n]), data(rawdata - 1), cnt(0), __size(n), CMP(cmp) {}
    void push(int x) override {
        if (cnt == __size) expand();
        cnt++;
        data[cnt] = x;
        up_maintain(cnt);
        return;
    }
    void pop() override {
        if (empty()) return;
        data[1] = data[cnt];
        --cnt;
        down_maintain(1);
        return;
    }
    bool empty() const override { return cnt == 0;}
    int size() const override { return cnt; }
    int top() const override { return data[1]; }
    ~my_priority_queue() {
        delete[] rawdata;
    }
private:
    int *rawdata, *data;
    int cnt, __size;
    CMP_T CMP;
    void up_maintain(int ind) {
        while (ind > 1) {
            if (CMP(data[ind], data[ind >> 1])) {
                swap(data[ind], data[ind >> 1]);
                ind >>= 1;
            } else {
                break;
            }
        }
        return;
    }
    void down_maintain(int ind) {
        while (ind << 1 <= cnt) {
            int temp = ind << 1;
            if ((ind << 1 | 1) <= cnt && CMP(data[ind << 1 | 1], data[temp])) temp++;
            if (!CMP(data[temp], data[ind])) return;
            swap(data[temp], data[ind]);
            ind = temp;
        }
        return;
    }
    void expand() {
        my_priority_queue q(2 * __size, CMP);
        while (!empty()) {
            q.push(top());
            pop();
        }
        this->Swap(q);
        return;
    }
    void Swap(my_priority_queue &q) {
        std::swap(this->rawdata, q.rawdata);
        std::swap(this->data, q.data);
        std::swap(this->cnt, q.cnt);
        std::swap(this->__size, q.__size);
    }

};


int main() {
    my_priority_queue q;
    int n;
    cin >> n;
    while (n--) {
        int a;
        cin >> a;
        q.push(a);
    }
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}


