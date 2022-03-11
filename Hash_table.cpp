/*************************************************************************
> File Name: Hash_table.cpp
> Author: zxq
> Mail: 1459190705@qq.com
> Created Time: Fri 11 Mar 2022 09:48:54 PM CST
************************************************************************/


#include<iostream>
#include<functional>
#include<vector>
using namespace std;


class Node {
    public:
    Node() = default;
    Node(string, int, Node*);
    string get_key();
    int& get_value();
    Node* next();
    void set_next(Node*);
    void insert(Node*);
    void erase_next();
    private:
    string __key;
    int __value;

    Node* __next;

};

class HashTable {
    public:
    typedef function<int(string)> HASH_FUNC_T;
    HashTable(int size, HASH_FUNC_T hash_func);
    bool insert(string, int);
    bool erase(string);
    bool find(string);
    int capacity();
    int& operator[](string);
    void swap(HashTable&);
    private:
    int __size, data_cnt;
    vector<Node> data;
    HASH_FUNC_T hash_func;
    void __expand();
    Node* __insert(string, int);
    Node* __find(string);

};


Node::Node(string key, int value, Node* next = nullptr)
:__key(key), __value(value), __next(next) {}
string Node::get_key() { return __key;  }
int& Node::get_value() { return __value;  }
Node* Node::next() { return __next;  }

void Node::set_next(Node* node)
{
    this->__next = node;
    return;

}
void Node::insert(Node* node)
{
    node->set_next(this->next());
    this->set_next(node);
    return;

}
void Node::erase_next()
{
    Node* temp = this->next();
    if (temp == nullptr) return;
    this->set_next(temp->next());
    delete temp;
    return;

}


HashTable::HashTable(int size, HASH_FUNC_T hash_func)
    :__size(size), data_cnt(0), data(size), hash_func(hash_func) {}

bool HashTable::insert(string key, int value = 0)
{
    if (data_cnt == 2 * __size) __expand();
    return __insert(key, value) != nullptr;

}
bool HashTable::erase(string key)
{
    if (!__find(key)) return false;
    int ind = hash_func(key) % __size;
    Node* p = &data[ind];
    while (p->next()->get_key() != key) p = p->next();
    p->erase_next();
    data_cnt--;
    return true;


}
bool HashTable::find(string key)
{
    return __find(key) != nullptr;

}
int HashTable::capacity() { return data_cnt;  }

int& HashTable::operator[](string key)
{
    if (!__find(key)) 
    insert(key, 0);
    return __find(key)->get_value();

}
void HashTable::swap(HashTable& h)
{
    std::swap(__size, h.__size);
    std::swap(data_cnt, h.data_cnt);
    std::swap(data, h.data);
    std::swap(hash_func, h.hash_func);
    return;

}

void HashTable::__expand()
{
    HashTable h(2 * __size, hash_func);
    for (int i = 0; i < __size; i++) {
        Node* p = data[i].next();
        while (p) {
            h.insert(p->get_key(), p->get_value());
            p = p->next();

        }

    }
    this->swap(h);
    return;

}
Node* HashTable::__insert(string key, int value)
{
    if (__find(key))  return nullptr;
    data_cnt++;
    int ind = hash_func(key) % __size;
    Node* temp = new Node(key, value);
    data[ind].insert(temp);
    return temp;

}
Node* HashTable::__find(string key)
{
    int ind = hash_func(key) % __size;
    Node* p = data[ind].next();
    while (p && p->get_key() != key) p = p->next();
    return p; //返回空或者找到

}



int BKDRHash(string s)
{
    int seed = 31;
    int h = 0;
    for (int i = 0; s[i]; i++) {
        h = h * seed + s[i];


    }
    return h & 0x7fffffff;


}

class APHash_Class {
    public:
    int operator()(string s)
    {
        int h = 0;
        for (int i = 0; s[i]; i++) {
            if (i % 2) {
                h = (h << 3) ^ s[i] ^ (h >> 5);



            }
            else {
                h = ~((h << 7) ^ s[i] ^ (h >> 11));


            }


        }
        return h & 0x7fffffff;


    }


};

int main()
{
    APHash_Class APHash;
    HashTable h1(10, BKDRHash);
    HashTable h2(10, APHash);
    int op;
    string s;
    cout << h1.capacity() << endl;
    cout << h2.capacity() << endl;
    h1["hello"] = 123;
    h1["world"] = 456;
    h1["haizei"] = 789;
    cout << h1.capacity() << endl;
    cout << h2.capacity() << endl;
    cout << h1["hello"] << " " << h1["world"] << " " << h1["hahaha"] << endl;
    while (cin >> op >> s) {
        switch (op) {
            case 0: {
                cout << "insert " << s << " to hash table 1 = ";
                cout << h1.insert(s) << endl;
                cout << "insert " << s << " to hash table 2 = ";
                cout << h2.insert(s) << endl;



            } break; // insert
            case 1: {
                cout << "erase " << s << " from hash table 1 = ";
                cout << h1.erase(s) << endl;
                cout << "erase " << s << " from hash table 2 = ";
                cout << h2.erase(s) << endl;



            } break; // erase
            case 2: {
                cout << "find " << s << " at hash table 1 = ";
                cout << h1.find(s) << endl;
                cout << "find " << s << " at hash table 2 = ";
                cout << h2.find(s) << endl;



            } break; // find


        }


    }
    return 0;


}



