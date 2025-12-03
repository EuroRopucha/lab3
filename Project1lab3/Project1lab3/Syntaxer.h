#pragma once

#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include "Lexer.h"
#include "BracketChecker.h"
#include <iostream>
using namespace std;

class Syntaxer {
public:
    void analyze(Queue<Token>& tokens) {
        if (tokens.isEmpty()) {
            throw invalid_argument("Empty expression is not allowed");
        }
        Stack<Token> brackets(tokens.size());
        Token prev(TokenType::Space, "");

        while (!tokens.isEmpty()) {
            Token curr = tokens.pop();
            switch (curr.type) {
            case TokenType::Number:
                if (prev.type == TokenType::Number) {
                    throw invalid_argument("Two numbers in a row are not allowed");
                }
                if (prev.type == TokenType::RightBracket) {
                    throw invalid_argument("A number cannot come immediately after ')'");
                }
                break;

            case TokenType::Operator:
                if (prev.type == TokenType::Operator) {
                    throw invalid_argument("Two operators in a row are not allowed");
                }
                if (prev.type == TokenType::LeftBracket) {
                    if (curr.value != "-") {
                        throw invalid_argument("Only unary minus is allowed immediately after '('");
                    }
                }
                if (prev.type == TokenType::Space || prev.type == TokenType::None) {
                    if (curr.value != "-") {
                        throw invalid_argument("Expression cannot start with this operator");
                    }
                }
                break;

            case TokenType::LeftBracket:
                if (prev.type == TokenType::Number) {
                    throw invalid_argument("A '(' cannot come immediately after a number");
                }
                if (prev.type == TokenType::RightBracket) {
                    throw invalid_argument("A '(' cannot come immediately after ')'");
                }
                brackets.push(curr);
                break;

            case TokenType::RightBracket:
                if (brackets.isEmpty()) {
                    throw invalid_argument("Unmatched closing bracket");
                }
                if (prev.type == TokenType::Operator) {
                    throw invalid_argument("A ')' cannot come immediately after an operator");
                }
                if (prev.type == TokenType::LeftBracket) {
                    throw invalid_argument("Empty brackets '()' are not allowed");
                }
                brackets.pop();
                break;

            case TokenType::Space:
                break;
            }
            prev = curr;
        }

        if (!brackets.isEmpty()) {
            throw invalid_argument("Unmatched closing bracket");
        }

        if (prev.type == TokenType::Operator || prev.type == TokenType::LeftBracket) {
            throw invalid_argument("The expression ends incorrectly");
        }

    }
};