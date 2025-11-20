#pragma once
#include "Token.h"
#include "Queue.h"
#include <string>
#include <stdexcept>
using namespace std;



class Lexer {

public:

    Queue<Token> tokenize(const string& input) {

        Queue<Token> output;


    }


};

























/*

#include <cctype>


class Lexer {
public:
    Queue<Token> tokenize(const std::string& input);
};
Queue<Token> Lexer::tokenize(const std::string& input) {
    Queue<Token> output;
    std::string buffer;
    State current = State::Start;

    for (char c : input) {
        CharType type = decodeChar(c);
        Action act = actionTable[(int)current][(int)type];
        act(c, buffer, output);
        current = transitionTable[(int)current][(int)type];
    }

    if (!buffer.empty()) {
        output.enqueue(Token(TokenType::Number, buffer));
    }

    return output;
}




enum class State {
    Start,
    Number,
    Error
};

enum class CharType {
    Digit,
    Operator,
    LeftBracket,
    RightBracket,
    Space,
    Unknown
};

CharType decodeChar(char c) {
    if (isdigit(c)) return CharType::Digit;
    if (c == '+' || c == '-' || c == '*' || c == '/') return CharType::Operator;
    if (c == '(') return CharType::LeftBracket;
    if (c == ')') return CharType::RightBracket;
    if (isspace(c)) return CharType::Space;
    return CharType::Unknown;
}
const int STATE_COUNT = 3;
const int CHAR_TYPE_COUNT = 6;

State transitionTable[STATE_COUNT][CHAR_TYPE_COUNT] = {
    // From Start
    {State::Number, State::Start, State::Start, State::Start, State::Start, State::Error},
    // From Number
    {State::Number, State::Start, State::Start, State::Start, State::Start, State::Error},
    // From Error
    {State::Error, State::Error, State::Error, State::Error, State::Error, State::Error}
};

typedef void (*Action)(char, std::string&, Queue<Token>&);

void emitDigit(char c, std::string& buffer, Queue<Token>& output) {
    buffer += c;
}

void flushNumber(char, std::string& buffer, Queue<Token>& output) {
    if (!buffer.empty()) {
        output.enqueue(Token(TokenType::Number, buffer));
        buffer.clear();
    }
}

void emitOperator(char c, std::string&, Queue<Token>& output) {
    output.enqueue(Token(TokenType::Operator, std::string(1, c)));
}

void emitBracket(char c, std::string&, Queue<Token>& output) {
    TokenType type = (c == '(') ? TokenType::LeftBracket : TokenType::RightBracket;
    output.enqueue(Token(type, std::string(1, c)));
}

void ignore(char, std::string&, Queue<Token>&) {}

void error(char c, std::string&, Queue<Token>&) {
    throw std::invalid_argument(std::string("Недопустимый символ: ") + c);
}

Action actionTable[STATE_COUNT][CHAR_TYPE_COUNT] = {
    // From Start
    {emitDigit, emitOperator, emitBracket, emitBracket, ignore, error},
    // From Number
    {emitDigit, flushNumber, flushNumber, flushNumber, flushNumber, error},
    // From Error
    {error, error, error, error, error, error}
};
*/