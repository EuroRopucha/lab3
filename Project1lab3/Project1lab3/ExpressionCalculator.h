#pragma once
#include "BracketChecker.h"
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"
#include <stdexcept>
#include <string>
using namespace std;

class ExpressionCalculator {

public:
    int calculate(const string& expression){

        BracketChecker checker;
        if (!checker.check(expression)) {
            throw invalid_argument("Incorrect brackets");
        }

        Lexer lexer;
        Queue<Token> tokens = lexer.tokenize(expression);

        Parser parser;
        Queue<Token> postfix = parser.toPostfix(tokens);

        Evaluator evaluator;
        return evaluator.evaluate(postfix);
    
    
    }
};

