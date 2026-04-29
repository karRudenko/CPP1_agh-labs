#pragma once

#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

/**
 * Bazowa klasa abstrakcyjna dla wszystkich węzłów drzewa AST.
 *
 * Każde wyrażenie:
 *   - może mieć dzieci dostępne przez operator[]
 *   - umie wyznaczyć swoją wartość przez eval(context)
 *   - umie przekonwertować się na czytelny string przez toString()
 *   - umie uprościć się przez simplify()
 *
 * Context to mapowanie: nazwa zmiennej -> wartość (double).
 */
class Expression {
public:
    using Context = std::map<std::string, double>;

    virtual ~Expression() = default;

    virtual const Expression& operator[](std::size_t index) const = 0;
    virtual double eval(const Context& ctx = {}) const = 0;
    virtual std::string toString() const = 0;
    virtual std::unique_ptr<Expression> simplify() const = 0;

protected:
    static bool isConstantWithValue(const Expression& e, double value);
};

// ─────────────────────────────────────────────
//  Constant
// ─────────────────────────────────────────────

class Constant : public Expression {
public:
    explicit Constant(double value) : value_(value) {}

    double getValue() const { return value_; }

    const Expression& operator[](std::size_t /*index*/) const override {
        throw std::out_of_range("Constant has no children");
    }

    double eval(const Context& /*ctx*/) const override { return value_; }

    std::string toString() const override {
        std::ostringstream oss;
        oss << value_;
        return oss.str();
    }

    std::unique_ptr<Expression> simplify() const override {
        return std::make_unique<Constant>(value_);
    }

private:
    double value_;
};

// ─────────────────────────────────────────────
//  Variable
// ─────────────────────────────────────────────

class Variable : public Expression {
public:
    explicit Variable(std::string name) : name_(std::move(name)) {}

    const std::string& getName() const { return name_; }

    const Expression& operator[](std::size_t /*index*/) const override {
        throw std::out_of_range("Variable has no children");
    }

    double eval(const Context& ctx) const override {
        const auto it = ctx.find(name_);
        if (it == ctx.end())
            throw std::runtime_error("Variable '" + name_ + "' not found in context");
        return it->second;
    }

    std::string toString() const override { return name_; }

    std::unique_ptr<Expression> simplify() const override {
        return std::make_unique<Variable>(name_);
    }

private:
    std::string name_;
};

// ─────────────────────────────────────────────
//  UnaryOperator  (negacja, symbol ~)
// ─────────────────────────────────────────────

/**
 * Węzeł z jednym dzieckiem — unarna negacja.
 * Symbol w RPN: ~ (tylda), żeby nie mylić z binarnym odejmowaniem.
 *
 * toString() -> "(-child)"
 * simplify() -> upraszcza dziecko; jeśli stało się Constant,
 *               zastępuje całość Constant(-value).
 */
class UnaryOperator : public Expression {
public:
    explicit UnaryOperator(std::unique_ptr<Expression> child)
        : child_(std::move(child)) {}

    const Expression& operator[](std::size_t index) const override {
        if (index == 0) return *child_;
        throw std::out_of_range("UnaryOperator has only one child (index 0)");
    }

    double eval(const Context& ctx) const override {
        return -child_->eval(ctx);
    }

    std::string toString() const override {
        return "(-" + child_->toString() + ")";
    }

    std::unique_ptr<Expression> simplify() const override {
        auto simplifiedChild = child_->simplify();
        const auto* c = dynamic_cast<const Constant*>(simplifiedChild.get());
        if (c != nullptr)
            return std::make_unique<Constant>(-c->getValue());
        return std::make_unique<UnaryOperator>(std::move(simplifiedChild));
    }

private:
    std::unique_ptr<Expression> child_;
};

// ─────────────────────────────────────────────
//  BinaryOperator
// ─────────────────────────────────────────────

/**
 * Węzeł wewnętrzny drzewa — wykonuje działanie binarne na dwóch dzieciach.
 *
 * simplify() działa w dwóch etapach:
 *   1. Rekurencyjnie upraszcza oba dzieci.
 *   2. Constant folding albo uproszczenia algebraiczne (zera/jedynki).
 */
class BinaryOperator : public Expression {
public:
    BinaryOperator(char op,
                   std::unique_ptr<Expression> left,
                   std::unique_ptr<Expression> right)
        : op_(op), left_(std::move(left)), right_(std::move(right)) {}

    char getOp() const { return op_; }

    const Expression& operator[](std::size_t index) const override {
        if (index == 0) return *left_;
        if (index == 1) return *right_;
        throw std::out_of_range("BinaryOperator has only two children (0 and 1)");
    }

    double eval(const Context& ctx) const override {
        const double l = left_->eval(ctx);
        const double r = right_->eval(ctx);
        switch (op_) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/':
                if (r == 0.0) throw std::runtime_error("Division by zero");
                return l / r;
            default:
                throw std::runtime_error(std::string("Unknown operator: ") + op_);
        }
    }

    std::string toString() const override {
        return "(" + left_->toString() + " " + op_ + " " + right_->toString() + ")";
    }

    std::unique_ptr<Expression> simplify() const override {
        // Krok 1: rekurencyjnie upraszczamy dzieci.
        auto sl = left_->simplify();
        auto sr = right_->simplify();

        const auto* cl = dynamic_cast<const Constant*>(sl.get());
        const auto* cr = dynamic_cast<const Constant*>(sr.get());

        // Krok 2a: constant folding — oba dzieci to stałe.
        if (cl != nullptr && cr != nullptr) {
            BinaryOperator tmp(op_,
                std::make_unique<Constant>(cl->getValue()),
                std::make_unique<Constant>(cr->getValue()));
            return std::make_unique<Constant>(tmp.eval({}));
        }

        // Krok 2b: uproszczenia algebraiczne.
        if (op_ == '+') {
            if (isConstantWithValue(*sr, 0.0)) return sl;   // x + 0 -> x
            if (isConstantWithValue(*sl, 0.0)) return sr;   // 0 + x -> x
        }
        if (op_ == '-') {
            if (isConstantWithValue(*sr, 0.0)) return sl;   // x - 0 -> x
            if (isConstantWithValue(*sl, 0.0))               // 0 - x -> (~x)
                return std::make_unique<UnaryOperator>(std::move(sr));
        }
        if (op_ == '*') {
            if (isConstantWithValue(*sr, 0.0)) return std::make_unique<Constant>(0.0);
            if (isConstantWithValue(*sl, 0.0)) return std::make_unique<Constant>(0.0);
            if (isConstantWithValue(*sr, 1.0)) return sl;   // x * 1 -> x
            if (isConstantWithValue(*sl, 1.0)) return sr;   // 1 * x -> x
        }
        if (op_ == '/') {
            if (isConstantWithValue(*sr, 1.0)) return sl;   // x / 1 -> x
        }

        // Brak uproszczenia — nowy węzeł z uproszczonymi dziećmi.
        return std::make_unique<BinaryOperator>(op_, std::move(sl), std::move(sr));
    }

private:
    char op_;
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

// ─────────────────────────────────────────────
//  Implementacja metody pomocniczej
// ─────────────────────────────────────────────

inline bool Expression::isConstantWithValue(const Expression& e, double value) {
    const auto* c = dynamic_cast<const Constant*>(&e);
    return c != nullptr && c->getValue() == value;
}
