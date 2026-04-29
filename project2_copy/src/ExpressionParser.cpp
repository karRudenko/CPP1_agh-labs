#include "ExpressionParser.h"

#include <cctype>
#include <cstdlib>
#include <sstream>
#include <stack>
#include <stdexcept>

// ═══════════════════════════════════════════════════════
//  Lexer — implementacja
// ═══════════════════════════════════════════════════════

bool Lexer::isBinaryOperator(const std::string& s) {
    return s.size() == 1 && (s[0] == '+' || s[0] == '-' ||
                              s[0] == '*' || s[0] == '/');
}

bool Lexer::isUnaryOperator(const std::string& s) {
    // Tylda ~ to jedyny operator unarny w naszym języku.
    return s == "~";
}

bool Lexer::isNumber(const std::string& s) {
    if (s.empty()) return false;
    char* endptr = nullptr;
    std::strtod(s.c_str(), &endptr);
    return endptr != s.c_str() && *endptr == '\0';
}

bool Lexer::isIdentifier(const std::string& s) {
    if (s.empty()) return false;
    if (!std::isalpha(static_cast<unsigned char>(s[0])) && s[0] != '_')
        return false;
    for (std::size_t i = 1; i < s.size(); ++i) {
        const unsigned char c = static_cast<unsigned char>(s[i]);
        if (!std::isalnum(c) && c != '_')
            return false;
    }
    return true;
}

Token Lexer::classifyToken(const std::string& raw) {
    // Kolejność ważna: operator unarny (~) przed identyfikatorem.
    if (isUnaryOperator(raw))   return { Token::Type::UNARY_OPERATOR,  raw };
    if (isBinaryOperator(raw))  return { Token::Type::BINARY_OPERATOR, raw };
    if (isNumber(raw))          return { Token::Type::NUMBER,           raw };
    if (isIdentifier(raw))      return { Token::Type::IDENTIFIER,       raw };

    throw std::runtime_error("Lexer: unrecognized token '" + raw + "'");
}

std::vector<Token> Lexer::tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::istringstream stream(input);
    std::string word;
    while (stream >> word) {
        tokens.push_back(classifyToken(word));
    }
    return tokens;
}

// ═══════════════════════════════════════════════════════
//  ExpressionParser — implementacja
// ═══════════════════════════════════════════════════════

std::unique_ptr<Expression> ExpressionParser::parseRPN(const std::string& input) {
    const std::vector<Token> tokens = Lexer::tokenize(input);

    std::stack<std::unique_ptr<Expression>> stack;

    for (const auto& token : tokens) {
        switch (token.type) {

            case Token::Type::NUMBER: {
                const double value = std::strtod(token.value.c_str(), nullptr);
                stack.push(std::make_unique<Constant>(value));
                break;
            }

            case Token::Type::IDENTIFIER: {
                stack.push(std::make_unique<Variable>(token.value));
                break;
            }

            case Token::Type::UNARY_OPERATOR: {
                // ~ zdejmuje jeden element ze stosu.
                if (stack.empty()) {
                    throw std::runtime_error(
                        "ExpressionParser: no operand for unary operator '~'");
                }
                auto child = std::move(stack.top()); stack.pop();
                stack.push(std::make_unique<UnaryOperator>(std::move(child)));
                break;
            }

            case Token::Type::BINARY_OPERATOR: {
                if (stack.size() < 2) {
                    throw std::runtime_error(
                        "ExpressionParser: not enough operands for operator '"
                        + token.value + "'");
                }
                // Stos: [...][lewy][prawy] → najpierw zdejmujemy prawy.
                auto right = std::move(stack.top()); stack.pop();
                auto left  = std::move(stack.top()); stack.pop();

                stack.push(std::make_unique<BinaryOperator>(
                    token.value[0], std::move(left), std::move(right)));
                break;
            }
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error(
            "ExpressionParser: malformed RPN expression (stack size = "
            + std::to_string(stack.size()) + " after parsing)");
    }

    return std::move(stack.top());
}
