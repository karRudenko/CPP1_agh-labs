#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Expression.h"

// ─────────────────────────────────────────────
//  Token
// ─────────────────────────────────────────────

/**
 * Pojedynczy token — najmniejsza jednostka wejścia.
 *
 * Cztery rodzaje tokenów:
 *   NUMBER          — literał liczbowy,   np. "3.14"
 *   IDENTIFIER      — nazwa zmiennej,     np. "x", "zmienna_1"
 *   BINARY_OPERATOR — jeden z: + - * /
 *   UNARY_OPERATOR  — tylda ~ (negacja unarna)
 */
struct Token {
    enum class Type { NUMBER, IDENTIFIER, BINARY_OPERATOR, UNARY_OPERATOR };

    Type        type;
    std::string value;
};

// ─────────────────────────────────────────────
//  Lexer
// ─────────────────────────────────────────────

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string& input);

private:
    static Token classifyToken(const std::string& raw);
    static bool  isBinaryOperator(const std::string& s);
    static bool  isUnaryOperator(const std::string& s);
    static bool  isNumber(const std::string& s);
    static bool  isIdentifier(const std::string& s);
};

// ─────────────────────────────────────────────
//  ExpressionParser
// ─────────────────────────────────────────────

/**
 * Buduje drzewo AST z wyrażenia w notacji RPN.
 *
 * Algorytm (stos):
 *   NUMBER / IDENTIFIER    → utwórz węzeł, wrzuć na stos
 *   BINARY_OPERATOR        → zdejmij dwa węzły (prawy, lewy),
 *                            utwórz BinaryOperator, wrzuć na stos
 *   UNARY_OPERATOR (~)     → zdejmij jeden węzeł,
 *                            utwórz UnaryOperator, wrzuć na stos
 */
class ExpressionParser {
public:
    static std::unique_ptr<Expression> parseRPN(const std::string& input);
};
