// ExpressionEvaluator.h
#pragma once
#include <iostream>

class ExpressionEvaluator {
public:
    ExpressionEvaluator();
    explicit ExpressionEvaluator(const char* initialExpression);
    ~ExpressionEvaluator();

    static double evaluate(const char* expression);
    double evaluate() const;
    char operator[](size_t index) const;
    void setExpression(const char* newExpression);
    bool setExpressionWithValidation(const char* newExpression);
    bool isValidExpression(const char* expression) const;
    static const char* concatenate(const char* expr1, const char* expr2);
    const char* getExpression() const;
    ExpressionEvaluator operator+(const ExpressionEvaluator& other) const;
    friend std::istream& operator>>(std::istream& in, ExpressionEvaluator& evaluator);
    friend std::ostream& operator<<(std::ostream& out, const ExpressionEvaluator& evaluator);

private:
    char* expression;
    static double applyOperator(double operand1, double operand2, char op);
    static int findClosingParenthesis(const char* expression, int startIndex);
    static const char* substring(const char* expression, int startIndex, int endIndex);
};

