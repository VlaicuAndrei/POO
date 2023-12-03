
// Calculator.h
#pragma once
#include <string>

class Calculator {
public:
    Calculator();
    Calculator(const std::string& expr);
    operator double() const;
    Calculator& operator++();
    Calculator operator++(int);
    virtual double evaluateExpression() = 0;

    const std::string& getExpression() const;
    void setExpression(const std::string& newExpression);

    char operator[](size_t index) const;
    bool isEmpty() const;

    friend std::istream& operator>>(std::istream& in, Calculator& calc);
    friend std::ostream& operator<<(std::ostream& out, const Calculator& calc);


    double getResult() const;
    void setResult(double newResult);
    bool isValidResult(double newResult) const;
private:
    bool isValidExpression(const std::string& expression) const;
    std::string expression;
    double result;
};
