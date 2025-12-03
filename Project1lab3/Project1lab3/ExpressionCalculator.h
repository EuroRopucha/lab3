#pragma once

#include <string>
#include "Lexer.h"
#include "Syntaxer.h"
#include "Parser.h"
#include "Calculator.h"
#include "Token.h"
#include "Stack.h"
#include "Queue.h"

class ExpressionCalculator {
public:
    int calculate(const std::string& expression) {

        Lexer lexer;
        Queue<Token> tokens = lexer.tokenize(expression);
        
        Syntaxer syntaxer;
        syntaxer.analyze(tokens);

        Parser parser; 
        Queue<Token> postfix = parser.toPostfix(tokens);

        Queue<Token> tmp2 = postfix;
        while (!tmp2.isEmpty()) {
            Token t = tmp2.pop();
            std::cout << "Postfix: type=" << (int)t.type << " value=" << t.value << "\n";
        }


        Calculator calculator;
        return calculator.calc(postfix);
    }
};
