/*************************************************************************
> File Name: my_vector.cpp
> Author: zxq
> Mail: 1459190705@qq.com
> Created Time: Fri 11 Mar 2022 10:25:06 AM CST
************************************************************************/

#include<iostream>
using namespace std;

template<typename T>
class Vector
{
    public:
    Vector() : start(0), finish(0), end_of_storage(0) {}
    Vector(int n, T value = T()) : start(new T[n]), finish(start), end_of_storage(start + n) {
        for ( T* first = start; first < end_of_storage; ++first ) {
            *first = value;

        }
        finish = end_of_storage;

    }
    Vector(const Vector<T>& vec) {
        start = (T*)malloc(sizeof(T) * vec.capicity());
        for (int i = 0; i < vec.capicity(); i++) {
            new(start + i) T(vec[i]);

        }
        finish = start + vec.size();
        end_of_storage = start + vec.capicity();
        return;

    }

    T& operator[](int pos) 
    {
        return *(start + pos);

    }
    const T& operator[](int pos) const 
    {
        return *(start + pos);

    }

    void push_back(const T value) 
    {
        if (finish != end_of_storage) {
            new(finish) T(value);
            ++finish;

        }
        else {
            const int old_size = size();;
            const int len = old_size == 0 ? 1 : 2 * old_size;
            T* new_start = (T*)malloc(len * sizeof(T));
            T* new_finish = new_start;
            for (int i = 0; i < old_size; i++) {
                new(new_start + i) T(*(start + i));
                ++new_finish;

            }
            new(new_finish) T(value);
            ++new_finish;
            delete[] start;
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;

        }

    }
T* insert(T* pos, const T& value) {
    int N = pos - begin();
    if (finish != end_of_storage && pos == end()) {
        new(pos) T(value);
        ++finish;
        return begin() + N;

    }
    else {
        if (finish != end_of_storage) {
            new(finish) T(*(finish - 1));
            ++finish;
            for (T* iter = finish - 1; iter > pos; iter--) {
                *iter = *(iter - 1);

            }
            *pos = value;

        }
        else {
            const int old_size = size();;
            const int len = old_size == 0 ? 1 : 2 * old_size;
            T* new_start = (T*)malloc(len * sizeof(T));
            T* new_finish = new_start;
            for (int i = 0; i < pos - start; i++) {
                new(new_start + i) T(*(start + i));
                ++new_finish;

            }
            new(new_finish) T(value);
            ++new_finish;
            for (T* i = pos; i != finish; i++) {
                new(new_finish) T(*i);
                ++new_finish;

            }
            delete[] start;
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;

        }

    }
    return begin() + N;

}



    void pop_back()
    {
        --finish;
        return;

    }

    int size() const { return finish - start;   }
    int capicity() const { return end_of_storage - start;  }
    T* begin() { return start;  }
    T* end() { return finish;  }
    T& front() { return *start;  }
    T& back() { return *(finish - 1);  }
    bool empty() { return begin() == end();  }
    ~Vector() {
        delete[] start;

    }
private:
    T* start;
    T* finish;
    T* end_of_storage;
};






int main() {
    int n;
    cin >> n;
    Vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (inti = 0; i < n; i++) cout << arr[i] << " "; 
    cout << endl;

}


