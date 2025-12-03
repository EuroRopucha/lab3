#pragma once

template<class T>
class Stack {
    int curr;
    int n;
    T* mem;
public:
    Stack(int _n = 0) {
        curr = -1;
        n = _n;
        mem = new T[n];
    }
    Stack(Stack& st) {
        curr = st.curr;
        n = st.n;
        mem = new T[n];
        for (int i = 0; i <= curr; i++) 
            mem[i] = st.mem[i];
    }
    ~Stack() {
        delete[] mem;
    }
    Stack& operator=(Stack& st) {
        if (this == &st)
            return *this;
        delete[] mem;
        n = st.n;
        curr = st.curr;
        mem = new T[n];
        for (int i = 0; i <= curr; i++) {
            mem[i] = st.mem[i];
        }
    }
    void push(const T& v) {
        if (curr == n - 1)
            throw - 1;
        mem[++curr] = v;
    }

    T pop() {
        if (curr < 0)
            throw - 1;
        return mem[curr--];
    }
    T& top() {
        if (curr < 0)
            throw - 1;
        return mem[curr];
    }

    bool isEmpty() {
        return curr == -1;
    }
};