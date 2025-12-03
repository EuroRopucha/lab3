#pragma once
#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include <string> 
#include <iostream>
using namespace std;

class Calculator {

private:
    int applyOperator(int a, int b, const string& op) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw invalid_argument("Division by zero");
            return a / b;
        }
        throw invalid_argument("Unknown operator: " + op);
    }

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
                if (curr.value == "u-") {
                    // унарный минус. один операнд
                    if (st.isEmpty()) throw invalid_argument("Missing operand for unary minus");
                    int a = st.pop();
                    st.push(-a);
                }
                else {
                    // бинарные операторы. два операнда
                    if (st.isEmpty()) throw invalid_argument("Missing operand for operator");
                    int b = st.pop();
                    if (st.isEmpty()) throw invalid_argument("Missing operand for operator");
                    int a = st.pop();

                    int res = applyOperator(a, b, curr.value);
                    st.push(res);
                }
                break;
            }

            case TokenType::LeftBracket:
            case TokenType::RightBracket:
            case TokenType::Space:
                // в постфиксной форме скобок и пробелов быть не должно
                break;
            }
        }

        if (st.isEmpty()) {
            throw invalid_argument("No result on stack");
        }
        int result = st.pop();

        if (!st.isEmpty()) {
            throw invalid_argument("Extra operands left on stack");
        }

        return result;
    }


};
