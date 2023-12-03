// Calculator.cpp
#include "Calculator.h"
#include "ExpressionEvaluator.h"
#include <iostream>

Calculator::Calculator() : result(0.0) {
    
}


Calculator::Calculator(const std::string& expr) : expression(expr) {
 
}

Calculator::operator double() const {
    return static_cast<double>(expression.length());
}

Calculator& Calculator::operator++() {
 
    result += 1.0;
    return *this;
}



const std::string& Calculator::getExpression() const {
    
    return expression;
}

void Calculator::setExpression(const std::string& newExpression) {
    if (isValidExpression(newExpression)) {
        expression = newExpression;
    }
    else {
        std::cerr << "Eroare: Expresia introdusa nu este valida.\n";
    }
}

bool Calculator::isValidExpression(const std::string& expression) const {
    int roundParenthesesCount = 0;
    int squareParenthesesCount = 0;

    for (char ch : expression) {
        if (!(std::isalnum(ch) || std::isspace(ch) ||
            ch == '(' || ch == ')' || ch == '[' || ch == ']' ||
            ch == '#' || ch == '^' || ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' || ch == '.')) {
            return false;
        }
        if (ch == '(') {
            roundParenthesesCount++;
        }
        else if (ch == ')') {
            roundParenthesesCount--;
            if (roundParenthesesCount < 0) {
                return false;
            }
        }
        if (ch == '[') {
            squareParenthesesCount++;
        }
        else if (ch == ']') {
            squareParenthesesCount--;
            if (squareParenthesesCount < 0) {
                return false;
            }
        }
    }
    return roundParenthesesCount == 0 && squareParenthesesCount == 0;
}

char Calculator::operator[](size_t index) const {
    if (index < expression.length()) {
        return expression[index];
    }
    else {
        std::cerr << "Index invalid pentru operatorul [].";
        return '\0'; 
    }
}

bool Calculator::isEmpty() const {
    
    return expression.empty();
}

std::istream& operator>>(std::istream& in, Calculator& calc) {
  
    std::cout << "Introduceti expresia matematica: ";
    getline(in, calc.expression);
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return in;
}

std::ostream& operator<<(std::ostream& out, const Calculator& calc) {
    out << "Expresie: " << calc.getExpression();
    return out;
}

double Calculator::getResult() const {
    return result;
}

void Calculator::setResult(double newResult) {
    if (isValidResult(newResult)) {
        result = newResult;
    }
    else {
        std::cerr << "Eroare: Valoarea nu este numerică.\n";
    }
}

bool Calculator::isValidResult(double newResult) const { 
    try {
        std::stod(std::to_string(newResult));
        return true; 
    }
    catch (const std::invalid_argument&) {
        return false; 
    }
}
