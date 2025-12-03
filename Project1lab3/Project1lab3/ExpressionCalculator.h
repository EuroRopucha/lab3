#pragma once

#include <string>
#include "BracketChecker.h"
#include "Lexer.h"
#include "Evaluator.h"
#include "Token.h"
#include "Stack.h"
#include "Queue.h"

class ExpressionCalculator {
public:
    int calculate(const std::string& expression);
};
/*
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
int ExpressionCalculator::calculate(const std::string& expression) {
    // 1. Лексический анализ -> токены (включая скобки)
    Lexer lexer;
    Queue<Token> tokens = lexer.tokenize(expression);

    // 2. Синтаксический анализ по токенам (баланс скобок, порядок, унарный минус)
    Syntaxer syntaxer;
    syntaxer.analyze(tokens); // бросает исключение при ошибке

    // 3. Преобразование инфикс -> постфикс (алгоритм сортировочной станции)
    Parser parser; // или InfixToPostfix
    Queue<Token> postfix = parser.toPostfix(tokens);

    // 4. Вычисление постфиксного выражения
    Evaluator evaluator;
    return evaluator.evaluate(postfix);
}
*/