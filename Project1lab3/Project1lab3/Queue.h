#pragma once

template<class T>
class Queue {
    T* arr;
    int n;
    int s, f;
public:
    Queue(int size) : n(size) {
        arr = new T[n];
        s = 0;
        f = n - 1;
    }
    Queue() : n(1) {
        arr = new T[n];
        s = 0;
        f = n - 1;
    }
    int next(int i) {
        return (i + 1) % n;
    }
    Queue(const Queue& q) {
        n = q.n;
        s = q.s;
        f = q.f;
        arr = new int[n];
        for (int i = s; i != next(f); i = next(i)) {
            arr[i] = q.arr[i];
        }
    }
    bool isEmpty() {
        return s == next(f);
    }
    bool isFull() {
        return s = next(next(f));
    }
    void push(int v) {
        if (isFull()) throw - 1;
        f = next(f);
        arr[f] = v;
    }
    int pop(){
        if(isEmpty()) throw - 1;
        int res = arr[s];
        s = next(s);
        return res;
    }
    int size() {
        return n;
    }

};