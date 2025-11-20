#pragma once
#include "Stack.h"
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

class BracketChecker {

public:

    bool check(const string& expression) {
        int len = expression.length();

        Stack<int> ind(len);
        Stack<int> errors(len);

        for (int i = 0; i < len; i++) {
            if (expression[i] == '(') {
                ind.Push(i);
            }
            else if (expression[i] == ')') {
                if (ind.isEmpty()) {
                    errors.Push(i);
                }
                else {
                    ind.Pop();
                }
            }
        }
        while (!ind.isEmpty()) {
            errors.Push(ind.Pop());
        }

        cout << "error:";
        while (!errors.isEmpty()) {
            cout << " " << errors.Pop() << ";";
        }
        cout << "\n";

        return ind.isEmpty();
    }
};










/*
class BracketChecker {

public:

	bool check(const string& expression) {
        int len = expression.length();
        Stack<char> brackets(len);
        for (int i = 0; i < len; i++) {
            if (expression[i] == '(') {
                brackets.Push('(');
            }
            else if (expression[i] == ')') {
                if (brackets.isEmpty()) {
                    throw std::invalid_argument("Unmatched closing bracket"); //return false;
                }
                else {
                    brackets.Pop();
                }
            }
        }
        return brackets.isEmpty();
	}
};

void check_brackets(const string& a) {
    int len = a.length();
    stack<int> ind(len);
    stack<int> errors(len);

    for (int i = 0; i < len; i++) {
        if (a[i] == '(') {
            ind.push(i);
        }
        else if (a[i] == ')') {
            if (ind.isempty()) {
                errors.push(i);
            }
            else {
                ind.pop();
            }
        }
    }

    while (!ind.isempty()) {
        errors.push(ind.pop());
    }

    cout << "error:";
    while (!errors.isempty()) {
        cout << " " << errors.pop() << ";";
    }
    cout << "\n";
}
*/