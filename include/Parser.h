#pragma once
#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include "map"
#include <iostream>
using namespace std;

class Parser {

    map<string, int> priorities = {
            {"u-", 3},
            {"*",  2},
            {"/",  2},
            {"+",  1},
            {"-",  1},
            {"(",  0},
            {")",  0}
    };

    int priority(const Token& t) {
        return priorities.at(t.value);
    }

public:

    Queue<Token> toPostfix(Queue<Token> tokens) {
        Stack<Token> opStack(tokens.size());
        Queue<Token> Postfix(tokens.size());

        while (!tokens.isEmpty()) {
            Token curr = tokens.pop();

            switch (curr.type) {
            case TokenType::Number:
                Postfix.push(curr);
                break;

            case TokenType::Operator:
                if (curr.value == "-") {
                    // проверка унарный минус
                    if (Postfix.isEmpty() ||
                        (!Postfix.isEmpty() && (opStack.isEmpty() || opStack.top().type == TokenType::LeftBracket))) {
                        Token unary(TokenType::Operator, "u-");
                        opStack.push(unary);
                        break;
                    }
                }
                // бинарный оператор
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
                while (!opStack.isEmpty() && opStack.top().type != TokenType::LeftBracket) {
                    Postfix.push(opStack.pop());
                }
                if (opStack.isEmpty()) {
                    throw invalid_argument("Unmatched closing bracket");
                }
                opStack.pop(); // убрать '('
                break;

            case TokenType::Space:
                break;
            }
        }

        while (!opStack.isEmpty()) {
            Token t = opStack.pop();
            if (t.type == TokenType::LeftBracket || t.type == TokenType::RightBracket) {
                throw std::invalid_argument("Unmatched closing bracket");
            }
            Postfix.push(t);
        }

        return Postfix;
    }
};
