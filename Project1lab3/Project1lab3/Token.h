#pragma once

enum class TokenType {
    Number,
    Operator,
    LeftBracket,
    RightBracket,
    Space
};

class Token {
public:
    TokenType type;
    std::string value;

    Token() : type(TokenType::Space), value("") {}
    Token(TokenType t, const std::string& v) : type(t), value(v) {}

    TokenType getType() { return type; }
    std::string getValue() { return value; }

};


