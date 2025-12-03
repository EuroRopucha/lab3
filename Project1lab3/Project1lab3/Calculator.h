#pragma once

#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include <string> 
#include <iostream>
using namespace std;

class Calculator {
public:
    int calc(Queue<Token> postfix) {
        Stack<int> st(postfix.size());

        while (!postfix.isEmpty()) {
            Token curr = postfix.pop();

            switch (curr.type) {
            case TokenType::Number: {
                int val = stoi(curr.value); // строка в int
                st.push(val);
                break;
            }

            case TokenType::Operator: {
                if (st.isEmpty()) throw std::invalid_argument("Missing operand for operator");
                int b = st.pop();
                if (st.isEmpty()) throw std::invalid_argument("Missing operand for operator");
                int a = st.pop();

                int res = applyOperator(a, b, curr.value);
                st.push(res);
                break;
            }

            case TokenType::LeftBracket:
            case TokenType::RightBracket:
            case TokenType::Space:
                // ¬ постфиксной форме скобок и пробелов быть не должно
                break;
            }
        }

        if (st.isEmpty()) {
            throw std::invalid_argument("No result on stack");
        }
        int result = st.pop();

        if (!st.isEmpty()) {
            throw std::invalid_argument("Extra operands left on stack");
        }

        return result;
    }

private:
    int applyOperator(int a, int b, const std::string& op) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw std::invalid_argument("Division by zero");
            return a / b; // целочисленное деление
        }
        throw std::invalid_argument("Unknown operator: " + op);
    }
};

