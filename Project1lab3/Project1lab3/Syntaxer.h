#pragma once

#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include "Lexer.h"
#include "BracketChecker.h"
#include <iostream>
using namespace std;

// 1. Начало выражения:
//допустимо: Number, LeftBracket, Operator(-)унарный минус
//недопустимо: Operator(+ * /), RightBracket
// 2. После Number:
//допустимо: Operator(+ - * /), RightBracket, конец строки
//недопустимо: Number
// 3. После Operator:
//допустимо: Number, LeftBracket
//недопустимо: Operator
// 4. После LeftBracket:
//допустимо: Number, LeftBracket,Operator(-)унарный минус
//недопустимо: Operator(+ * /), RightBracket
// 5. После RightBracket:
//допустимо: Operator(+ - * /), RightBracket, конец строки
//недопустимо: Number
// 6. Конец выражения:
//допустимо: Number, RightBracket
//недопустимо: Operator(+ - * /), LeftBracket


class Syntaxer {
public:
    bool analyze(Queue<Token>& tokens) {
        if (tokens.isEmpty()) {
            throw std::invalid_argument("Empty expression is not allowed");
        }

        Stack<Token> brackets(tokens.size()); // стек для проверки скобок
        Token prev(TokenType::Space, "");     // фиктивный предыдущий токен

        while (!tokens.isEmpty()) {
            Token curr = tokens.pop();

            switch (curr.type) {
            case TokenType::Number:
                // Проверка: после Number не может идти другой Number или LeftBracket
                // Допустимо: Operator, RightBracket, конец
                break;

            case TokenType::Operator:
                // Проверка: оператор не может идти в начале (кроме унарного '-')
                // После Number или RightBracket допустим
                // После другого Operator недопустим
                break;

            case TokenType::LeftBracket:
                // Проверка: после LeftBracket допустим Number, другой LeftBracket, унарный '-'
                // Недопустим сразу RightBracket или бинарный оператор
                brackets.Push(curr);
                break;

            case TokenType::RightBracket:
                // Проверка: стек скобок не пуст
                if (brackets.isEmpty()) {
                    throw std::invalid_argument("Лишняя закрывающая скобка");
                }
                brackets.Pop();
                // После RightBracket допустим Operator, другой RightBracket, конец
                break;

            case TokenType::Space:
                // Пробелы можно игнорировать
                break;
            }

            prev = curr; // обновляем предыдущий токен
        }

        // Проверка: стек скобок должен быть пуст
        if (!brackets.isEmpty()) {
            throw std::invalid_argument("Не все скобки закрыты");
        }

        // Проверка: выражение не должно заканчиваться оператором или LeftBracket
        if (prev.type == TokenType::Operator || prev.type == TokenType::LeftBracket) {
            throw std::invalid_argument("Выражение некорректно заканчивается");
        }

        return true; // если дошли сюда — синтаксис корректен
    }
};