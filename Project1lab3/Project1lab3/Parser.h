

/*
#pragma once
#include "Queue.h"
#include "Token.h"
#include "Stack.h"

class Parser {
public:
    Queue<Token> toPostfix(Queue<Token> infix);
};


#include "Parser.h"
#include <map>

Queue<Token> Parser::toPostfix(Queue<Token> infix) {
    Queue<Token> output;
    Stack<Token> operators(infix.size());
    std::map<std::string, int> precedence = {
        {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}
    };

    while (!infix.empty()) {
        Token token = infix.dequeue();
        if (token.type == TokenType::Number) {
            output.enqueue(token);
        }
        else if (token.type == TokenType::Operator) {
            while (!operators.isEmpty() &&
                operators.Top().type == TokenType::Operator &&
                precedence[operators.Top().value] >= precedence[token.value]) {
                output.enqueue(operators.Pop());
            }
            operators.Push(token);
        }
        else if (token.type == TokenType::LeftBracket) {
            operators.Push(token);
        }
        else if (token.type == TokenType::RightBracket) {
            while (!operators.isEmpty() && operators.Top().type != TokenType::LeftBracket) {
                output.enqueue(operators.Pop());
            }
            if (!operators.isEmpty()) {
                operators.Pop(); // remove '('
            }
        }
    }

    while (!operators.isEmpty()) {
        output.enqueue(operators.Pop());
    }

    return output;
}

*/