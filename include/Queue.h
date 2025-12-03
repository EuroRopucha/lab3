#pragma once

template<class T>
class Queue {
	size_t n;
	T* pMem;
	size_t s, f;
public:
	Queue() : n(0), pMem(nullptr), s(0), f(0) {}
	Queue(size_t sz) : n(sz) {
		pMem = new T[n];
		s = 0;
		f = n - 1;
	}
	Queue(const Queue& other) : n(other.n), s(other.s), f(other.f) {
		pMem = new T[n];
		for (size_t i = 0; i < n; i++) {
			pMem[i] = other.pMem[i];
		}
	}

	~Queue() {
		delete[] pMem;
	}
	size_t size() {
		return n;
	}
	int next(int i) {
		return (i + 1) % n;
	}
	bool isFull() {
		return s == next(next(f));
	}
	bool isEmpty() {
		return s == next(f);
	}
	void push(const T& el) {
		if (isFull()) {
			throw -1;
		}
		f = next(f);
		pMem[f] = el;
	}
	T pop() {
		if (isEmpty()) {
			throw -1;
		}
		T res = pMem[s];
		s = next(s);
		return res;
	}
	T& front() {
		if (isEmpty()) {
			throw -1;
		}
		return pMem[s];
	}
};