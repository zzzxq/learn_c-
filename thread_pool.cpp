/*************************************************************************
> File Name: thread_pool.cpp
> Author: zxq
> Mail: 1459190705@qq.com
> Created Time: Tue 29 Mar 2022 09:29:50 PM CST
************************************************************************/

#include<iostream>
#include<unordered_map>
#include<vector>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<thread>
#include<functional>

using namespace std;


class Task 
{
public:
    template<typename FUNC_T, typename ...ARGS>
    Task(FUNC_T func, ARGS ...args) {
        this->func = bind(func, forward<ARGS>(args)...);
    }
    void run() {
        this->func();
        return;
    }
private:
    function<void()> func;
};

class ThreadPool
{
public:
    ThreadPool(int n) : starting(false), thread_size(n), threads(n) 
    {
        this->start();
        return;
    }
    void start()
    {
        if (starting == true) return;
        for (int i = 0; i < thread_size; i++) {
            threads[i] = new thread(&ThreadPool::worker, this);
        }
        starting = true;
        return;
    }
    void worker() 
    {
        auto id = this_thread::get_id();
        running[id] = true;
        while (running[id]) {
            Task *t = get_task();
            t->run();
            delete t;
        }
        return;
    }
    void stop()
    {
        if (starting == false) return;
        for (int i = 0; i < thread_size; i++) {
            this->add_task(&ThreadPool::stop_running, this);
        }
        for (int i = 0; i < thread_size; i++) {
            threads[i]->join();
        }
        for (int i = 0; i <thread_size; i++) {
            delete threads[i];
            threads[i] = nullptr;
        }
        starting = false;
        return;

    }
    template<typename FUNC_T, typename ...ARGS>
    void add_task(FUNC_T func, ARGS ...args) 
    {
        unique_lock<mutex> lock(m_mutex);
        tasks.push(new Task(func, forward<ARGS>(args)...));
        m_cond.notify_one();
        lock.unlock();
        return;
    }

    ~ThreadPool()
    {
        this->stop();
        while (tasks.empty()) {
            delete tasks.front();
            tasks.pop();
        }

    }



private:
    bool starting;
    int thread_size;
    vector<thread*> threads;
    std::mutex m_mutex;
    condition_variable m_cond;
    unordered_map<decltype(this_thread::get_id()), bool> running;
    queue<Task *> tasks;
    void stop_running() 
    {
        auto id = this_thread::get_id();
        running[id] = false;
        return;
    }

    Task* get_task() 
    {
        unique_lock<mutex> lock(m_mutex);
        while (tasks.empty()) { m_cond.wait(lock); }
        Task *t = tasks.front();
        tasks.pop();
        lock.unlock();
        return t;
    }
    };



bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;

    }
    return true;

}

int prime_count(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        if (is_prime(i)) ans += 1;

    }
    return ans;

}

void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << " begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << " done" << endl;
    return;

}


#define batch 500000

int main() {
    ThreadPool tp(5);
    int ret[10];
    for (int i = 0, j = 1; i <10; i++, j += batch) {
        tp.add_task(worker, j, j + batch - 1, ref(ret[i]));
    }
    tp.stop();
    int ans = 0;
    for (auto x : ret) ans += x;
    cout << ans << endl;
    return 0;

}




