#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <stdexcept>
#include <cctype>

using namespace std;

// Простой токен
struct Token {
    string text;   // исходный текст токена ("123", "x", "+", "u-")
    bool isNumber = false;
    bool isIdent = false;
    bool isOp = false;
    bool isLParen = false;
    bool isRParen = false;
    double number = 0.0;
};

// Лексер: строка -> вектор токенов
vector<Token> lex(const string& s) {
    vector<Token> out;
    size_t i = 0, n = s.size();
    while (i < n) {
        char c = s[i];
        if (isspace((unsigned char)c)) { ++i; continue; }
        if (isdigit((unsigned char)c) || (c == '.' && i + 1 < n && isdigit((unsigned char)s[i + 1]))) {
            size_t j = i;
            bool dot = false;
            while (j < n && (isdigit((unsigned char)s[j]) || (!dot && s[j] == '.'))) {
                if (s[j] == '.') dot = true;
                ++j;
            }
            string tok = s.substr(i, j - i);
            Token t; t.text = tok; t.isNumber = true; t.number = stod(tok);
            out.push_back(t);
            i = j;
            continue;
        }
        if (isalpha((unsigned char)c)) {
            size_t j = i;
            while (j < n && (isalnum((unsigned char)s[j]) || s[j] == '_')) ++j;
            string tok = s.substr(i, j - i);
            Token t; t.text = tok; t.isIdent = true;
            out.push_back(t);
            i = j;
            continue;
        }
        if (c == '(') { Token t; t.text = "("; t.isLParen = true; out.push_back(t); ++i; continue; }
        if (c == ')') { Token t; t.text = ")"; t.isRParen = true; out.push_back(t); ++i; continue; }
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            Token t; t.text = string(1, c); t.isOp = true; out.push_back(t); ++i; continue;
        }
        throw runtime_error("Lex error: unexpected character at position " + to_string(i));
    }

    // Обработка унарного минуса: если '-' в начале или после '(' или другого оператора -> "u-"
    for (size_t k = 0; k < out.size(); ++k) {
        if (out[k].isOp && out[k].text == "-") {
            bool unary = false;
            if (k == 0) unary = true;
            else if (out[k - 1].isOp || out[k - 1].isLParen) unary = true;
            if (unary) out[k].text = "u-";
        }
    }

    return out;
}

// Приоритеты и арность операторов
int precedence(const string& op) {
    if (op == "u-") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}
int arity(const string& op) {
    if (op == "u-") return 1;
    return 2;
}
bool isLeftAssociative(const string& op) {
    if (op == "u-") return false;
    return true;
}

// Перевод в постфикс (shunting-yard)
vector<Token> toPostfix(const vector<Token>& infix) {
    vector<Token> out;
    stack<Token> st;
    for (const Token& t : infix) {
        if (t.isNumber || t.isIdent) {
            out.push_back(t);
        }
        else if (t.isOp) {
            string op1 = t.text;
            while (!st.empty() && st.top().isOp) {
                string op2 = st.top().text;
                int p1 = precedence(op1), p2 = precedence(op2);
                if ((isLeftAssociative(op1) && p1 <= p2) || (!isLeftAssociative(op1) && p1 < p2)) {
                    out.push_back(st.top()); st.pop();
                }
                else break;
            }
            st.push(t);
        }
        else if (t.isLParen) {
            st.push(t);
        }
        else if (t.isRParen) {
            bool found = false;
            while (!st.empty()) {
                Token top = st.top(); st.pop();
                if (top.isLParen) { found = true; break; }
                out.push_back(top);
            }
            if (!found) throw runtime_error("Mismatched parentheses");
        }
    }
    while (!st.empty()) {
        if (st.top().isLParen || st.top().isRParen) throw runtime_error("Mismatched parentheses");
        out.push_back(st.top()); st.pop();
    }
    return out;
}

// Вычисление постфиксной формы. vars — значения переменных.
double evalPostfix(const vector<Token>& post, const unordered_map<string, double>& vars) {
    stack<double> st;
    for (const Token& t : post) {
        if (t.isNumber) {
            st.push(t.number);
        }
        else if (t.isIdent) {
            auto it = vars.find(t.text);
            if (it == vars.end()) throw runtime_error("Unknown identifier: " + t.text);
            st.push(it->second);
        }
        else if (t.isOp) {
            string op = t.text;
            int a = arity(op);
            if ((int)st.size() < a) throw runtime_error("Not enough operands for operator " + op);
            if (a == 1) {
                double v = st.top(); st.pop();
                if (op == "u-") st.push(-v);
                else throw runtime_error("Unknown unary op: " + op);
            }
            else {
                double right = st.top(); st.pop();
                double left = st.top(); st.pop();
                if (op == "+") st.push(left + right);
                else if (op == "-") st.push(left - right);
                else if (op == "*") st.push(left * right);
                else if (op == "/") {
                    if (right == 0.0) throw runtime_error("Division by zero");
                    st.push(left / right);
                }
                else throw runtime_error("Unknown binary op: " + op);
            }
        }
        else {
            throw runtime_error("Unexpected token in postfix");
        }
    }
    if (st.size() != 1) throw runtime_error("Evaluation error: stack has extra items");
    return st.top();
}

// Вспомогательная печать постфикса (для отладки)
string postfixToString(const vector<Token>& post) {
    string out;
    for (const Token& t : post) {
        if (!out.empty()) out += ' ';
        out += t.text;
    }
    return out;
}

// Пример использования
int main() {
    try {
        string expr;
        cout << "Enter expression: ";
        if (!getline(cin, expr)) return 0;
        auto toks = lex(expr);
        auto post = toPostfix(toks);
        cout << "Postfix: " << postfixToString(post) << "\n";

        // Собираем переменные (уникально)
        unordered_map<string, double> vars;
        for (const Token& t : toks) if (t.isIdent) vars.emplace(t.text, 0.0);
        for (auto& kv : vars) {
            cout << "Enter value for " << kv.first << ": ";
            double v; if (!(cin >> v)) throw runtime_error("Bad input");
            kv.second = v;
        }

        double result = evalPostfix(post, vars);
        cout << "Result: " << result << "\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
