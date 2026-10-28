#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

class Expression {
public:
    virtual ~Expression() = default;
    virtual double evaluate(double x) const = 0;
    virtual std::shared_ptr<Expression> derivative() const = 0;
    virtual std::string toString() const = 0;
    virtual bool isConstant() const {
        return false;
    }
    virtual double constantValue() const {
        throw std::runtime_error("No es una constante");
    }
};
using Expr = std::shared_ptr<Expression>;

class Constant : public Expression {
    double value_;
public:
    explicit Constant(double value) : value_(value) {}
    double evaluate(double) const override {
        return value_;
    }
    Expr derivative() const override {
        return std::make_shared<Constant>(0);
    }
    std::string toString() const override {
        std::ostringstream o;
        o << value_;
        return o.str();
    }
    bool isConstant() const override {
        return true;
    }
    double constantValue() const override {
        return value_;
    }
    double value() const {
        return value_;
    }
};
class Variable : public Expression {
public:
    double evaluate(double x) const override {
        return x;
    }
    Expr derivative() const override {
        return std::make_shared<Constant>(1);
    }
    std::string toString() const override {
        return "x";
    }
};
class BinaryOperation : public Expression {
protected:
    Expr left_, right_;
public:
    BinaryOperation(Expr left, Expr right) : left_(std::move(left)), right_(std::move(right)) {}
};
class Add : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    double evaluate(double x) const override {
        return left_->evaluate(x) + right_->evaluate(x);
    }
    Expr derivative() const override {
        return std::make_shared<Add>(left_->derivative(), right_->derivative());
    }
    std::string toString() const override {
        return "(" + left_->toString() + " + " + right_->toString() + ")";
    }
};
class Multiply : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    double evaluate(double x) const override {
        return left_->evaluate(x) * right_->evaluate(x);
    }
    Expr derivative() const override {
        return std::make_shared<Add>(std::make_shared<Multiply>(left_->derivative(), right_),
                                     std::make_shared<Multiply>(left_, right_->derivative()));
    }
    std::string toString() const override {
        return "(" + left_->toString() + " * " + right_->toString() + ")";
    }
};
class Power : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;
    double evaluate(double x) const override {
        return std::pow(left_->evaluate(x), right_->evaluate(x));
    }
    Expr derivative() const override {
        auto u = left_; auto v = right_;
        if (v->isConstant()) {
            const double n = v->constantValue();
            return std::make_shared<Multiply>(
                    std::make_shared<Multiply>(std::make_shared<Constant>(n),
                                               std::make_shared<Power>(u, std::make_shared<Constant>(n - 1))),
                    u->derivative());
        }
        throw std::runtime_error("Power::derivative: esta implementación requiere exponente constante");
    }
    std::string toString() const override { return "(" + left_->toString() + " ^ " + right_->toString() + ")";
    }
};
class UnaryFunction : public Expression {
protected:
    Expr operand_;
public:
    explicit UnaryFunction(Expr operand) : operand_(std::move(operand)) {}
};
class Sin;
class Cos : public UnaryFunction {
public:
    using UnaryFunction::UnaryFunction;
    double evaluate(double x) const override { return std::cos(operand_->evaluate(x)); }
    Expr derivative() const override;
    std::string toString() const override { return "cos(" + operand_->toString() + ")"; }
};
class Sin : public UnaryFunction {
public:
    using UnaryFunction::UnaryFunction;
    double evaluate(double x) const override { return std::sin(operand_->evaluate(x)); }
    Expr derivative() const override {
        return std::make_shared<Multiply>(std::make_shared<Cos>(operand_), operand_->derivative());
    }
    std::string toString() const override { return "sin(" + operand_->toString() + ")";
    }
};
inline Expr Cos::derivative() const {
    return std::make_shared<Multiply>(
            std::make_shared<Multiply>(std::make_shared<Constant>(-1), std::make_shared<Sin>(operand_)),
            operand_->derivative());
}

int main() {
    auto x = std::make_shared<Variable>();

    Expr expr = std::make_shared<Multiply>(
            std::make_shared<Add>(
                    std::make_shared<Power>(
                            x,
                            std::make_shared<Constant>(2)
                    ),
                    std::make_shared<Multiply>(
                            std::make_shared<Constant>(3),
                            x
                            )
                    ),
                    std::make_shared<Sin>(x)
            );

    auto deriv = expr->derivative();

    std::cout << "f(x) = " << expr->toString() << std::endl;
    std::cout << "f'(x) = " << deriv->toString() << std::endl;

    std::cout << "f(2) = " << expr->evaluate(2) << std::endl;
    std::cout << "f'(2) = " << deriv->evaluate(2) << std::endl;
}
