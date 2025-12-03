#pragma once

#include <string>
#include "Lexer.h"
#include "Syntaxer.h"
#include "Parser.h"
#include "Calculator.h"
#include "Token.h"
#include "Stack.h"
#include "Queue.h"

void printQueue(Queue<Token> q, const std::string& stage) {
    std::cout << "\n--- " << stage << " ---\n";
    while (!q.isEmpty()) {
        Token t = q.pop();
        std::cout << "Token value=" << t.value << "\n";
    }
}
class ExpressionCalculator {
public:
    int calculate(const std::string& expression) {
        Lexer lexer;
        Queue<Token> tokens = lexer.tokenize(expression);

        printQueue(tokens, "After Lexer");

        Syntaxer syntaxer;
        syntaxer.analyze(tokens);

        printQueue(tokens, "After Syntaxer");

        Parser parser;
        Queue<Token> postfix = parser.toPostfix(tokens);

        printQueue(postfix, "After Parser (Postfix)");

        Calculator calculator;
        return calculator.calc(postfix);
    }
};
