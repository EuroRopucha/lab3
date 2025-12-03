#pragma once
#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include <iostream>
using namespace std;

class Parser {
public:
    Queue<Token> toPostfix(Queue<Token> tokens) {

        Stack<Token> opStack(tokens.size());
        Queue<Token> Postfix(tokens.size());

        while (!tokens.isEmpty()) {
            Token curr = tokens.pop();
            cout << "k";
            switch (curr.type) {
            case TokenType::Number:
                Postfix.push(curr);
                break;

            case TokenType::Operator:
                if (curr.value == "-") {
                    // Проверка: унарный минус?
                    if (Postfix.isEmpty() ||
                        (!Postfix.isEmpty() && (opStack.isEmpty() || opStack.top().type == TokenType::Operator || opStack.top().type == TokenType::LeftBracket))) {
                        // Унарный минус: создаём специальный токен
                        Token unary(TokenType::Operator, "u-");
                        opStack.push(unary);
                        break;
                    }
                }

                // обычный бинарный оператор
                while (!opStack.isEmpty() &&
                    opStack.top().type == TokenType::Operator &&
                    priority(opStack.top()) >= priority(curr)) {
                    Postfix.push(opStack.pop());
                }
                opStack.push(curr);
                break;

            case TokenType::LeftBracket:
                opStack.push(curr);
                break;

            case TokenType::RightBracket:
                // Выбрасываем операторы до '('
                while (!opStack.isEmpty() && opStack.top().type != TokenType::LeftBracket) {
                    Postfix.push(opStack.pop());
                }
                if (opStack.isEmpty()) {
                    throw std::invalid_argument("Mismatched parentheses");
                }
                opStack.pop(); // убрать '('
                break;

            case TokenType::Space:
                break;
            }
        }

        // В конце переносим оставшиеся операторы
        while (!opStack.isEmpty()) {
            Token t = opStack.pop();
            if (t.type == TokenType::LeftBracket || t.type == TokenType::RightBracket) {
                throw std::invalid_argument("Mismatched parentheses at end");
            }
            Postfix.push(t);
        }

        return Postfix;
    }

private:
    int priority(const Token& t) {
        if (t.value == "u-") return 3;
        if (t.value == "*" || t.value == "/") return 2;
        if (t.value == "+" || t.value == "-") return 1;
        return 0;
    }
};