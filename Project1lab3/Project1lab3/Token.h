#pragma once
#include <string>
using namespace std;

enum class TokenType {
    Number,
    Operator,
    LeftBracket,
    RightBracket
};

class Token {
public:
    TokenType type;
    string value;

    Token(TokenType t, const string& v) : type(t), value(v) {}
};

