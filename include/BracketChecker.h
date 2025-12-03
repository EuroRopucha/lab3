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
                ind.push(i);
            }
            else if (expression[i] == ')') {
                if (ind.isEmpty()) {
                    errors.push(i);
                }
                else {
                    ind.pop();
                }
            }
        }
        while (!ind.isEmpty()) {
            errors.push(ind.pop());
        }

        if (!errors.isEmpty()) {
            cout << "Bracket errors at:";
            while (!errors.isEmpty()) {
                cout << " " << errors.pop() << ";";
            }
            cout << "\n";
            throw invalid_argument("Unmatched brackets found");
        }
        return true;
    }
};
