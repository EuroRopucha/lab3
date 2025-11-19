#pragma once





























/*

#pragma once
#include "Queue.h"
#include "Token.h"
#include "Stack.h"

class Evaluator {
public:
    int evaluate(Queue<Token> postfix);
};

#include "Evaluator.h"
#include <stdexcept>

int Evaluator::evaluate(Queue<Token> postfix) {
    Stack<int> values(postfix.size());

    while (!postfix.empty()) {
        Token token = postfix.dequeue();
        if (token.type == TokenType::Number) {
            values.Push(std::stoi(token.value));
        }
        else if (token.type == TokenType::Operator) {
            int b = values.Pop();
            int a = values.Pop();
            int result = 0;

            if (token.value == "+") result = a + b;
            else if (token.value == "-") result = a - b;
            else if (token.value == "*") result = a * b;
            else if (token.value == "/") {
                if (b == 0) throw std::invalid_argument("Division by zero");
                result = a / b;
            }

            values.Push(result);
        }
    }

    return values.Pop();
}
*/
