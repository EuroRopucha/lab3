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
        Stack<int> ind(len);     // индексы открывающих скобок
        Stack<int> errors(len);  // индексы ошибок

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

        if (!errors.isEmpty()) {
            cout << "Bracket errors at:";
            while (!errors.isEmpty()) {
                cout << " " << errors.Pop() << ";";
            }
            cout << "\n";
            throw invalid_argument("Unmatched brackets found");
        }
        return true;
    }
};
