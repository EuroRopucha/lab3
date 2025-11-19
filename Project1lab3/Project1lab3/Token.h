#pragma once
#include <string>

enum class TokenType {
    Number,
    Operator,
    LeftBracket,
    RightBracket
};

class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

