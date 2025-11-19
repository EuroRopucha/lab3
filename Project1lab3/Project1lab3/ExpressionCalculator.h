#pragma once

#include <string>
#include "BracketChecker.h"
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"

class ExpressionCalculator {
public:
    int calculate(const std::string& expression);
};

#include "ExpressionCalculator.h"
#include <stdexcept>

int ExpressionCalculator::calculate(const std::string& expression) {
    // 1. Проверка скобок
    BracketChecker checker;
    if (!checker.check(expression)) {
        throw std::invalid_argument("Некорректные скобки в выражении");
    }

    // 2. Лексический анализ
    Lexer lexer;
    Queue<Token> tokens = lexer.tokenize(expression);

    // 3. Преобразование в постфиксную форму
    Parser parser;
    Queue<Token> postfix = parser.toPostfix(tokens);

    // 4. Вычисление результата
    Evaluator evaluator;
    return evaluator.evaluate(postfix);
}
