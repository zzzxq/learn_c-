/*************************************************************************
> File Name: function.cpp
> Author: zxq
> Mail: 1459190705@qq.com
> Created Time: Sat 12 Mar 2022 11:25:14 AM CST
************************************************************************/

#include<iostream>
using namespace std;



template<typename T, typename ...ARGS>
class Base
{
public:
    virtual T run(ARGS ...args) = 0;
    virtual Base<T, ARGS...>* get_copy() = 0;
    virtual ~Base() {}
};


template<typename T, typename ...ARGS>
class normal_function : public Base<T, ARGS...>
{
public:
    normal_function(T (*ptr)(ARGS...)) : ptr(ptr) {}
    T run(ARGS ...args) override {
        return ptr(forward<ARGS>(args)...);
    }
    Base<T, ARGS...>* get_copy() override {
        return new normal_function(*this);
    }
private:
    T(*ptr) (ARGS...);
};


template<typename CLASS_T, typename T, typename ...ARGS>
class functor : public Base<T, ARGS...>
{
public:
    functor(CLASS_T obj) : obj(obj) {}
    T run(ARGS ...args) override {
        return obj(forward<ARGS>(args)...);
    }
    Base<T, ARGS...>* get_copy() override {
        return new functor(*this);
    }
private:
    CLASS_T obj;
};

template<typename T, typename ...ARGS> class function {};
template<typename T, typename ...ARGS>
class function<T(ARGS...)> 
{
public:
    function(T (*ptr)(ARGS...)) : ptr(new normal_function<T, ARGS...>(ptr)) {}
    template<typename CLASS_T>
    function(CLASS_T obj) : ptr(new functor<CLASS_T, T, ARGS...>(obj)) {}
    T operator()(ARGS ...args) {
        return ptr->run(forward<ARGS>(args)...);
    }
    function operator=(function<T(ARGS...)> &func) {
        delete this->ptr;
        this->ptr = func.ptr->get_copy();
        return *this;
    }
private:
    Base<T, ARGS...> *ptr;
};







int add(int a, int b) {
    cout << "normal function ";
    return a + b;

}

class ADD_MULT {
    public:
    ADD_MULT(int x) : x(x) {}
    int operator()(int a, int b) {
        cout << "functor ";
        return (a + b) * 2;

    }
    private :
    int x;

};
int main() {
    ADD_MULT add_mult(2);
    function<int(int, int)> f1 = add;
    function<int(int, int)> f2 = add_mult;
    cout << f1(3, 4) << endl;
    cout << f2(3, 4) << endl;
    function<int(int, int)> f3 = [](int a, int b) { return a * b;};
    cout << f3(3, 4) << endl;
    return 0;

}














