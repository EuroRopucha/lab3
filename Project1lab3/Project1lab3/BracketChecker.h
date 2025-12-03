#pragma once
#include "Stack.h"
#include <string>
#include <stdexcept>
using namespace std;

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
                    throw std::invalid_argument("Unmatched closing bracket");
                }
                else {
                    brackets.Pop();
                }
            }
        }
        return brackets.isEmpty();
	}
};
