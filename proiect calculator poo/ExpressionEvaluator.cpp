// ExpressionEvaluator.cpp
#include "ExpressionEvaluator.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>

ExpressionEvaluator::ExpressionEvaluator() {
    expression = new char[1];
    expression[0] = '\0';
}

ExpressionEvaluator::ExpressionEvaluator(const char* initialExpression) {
    setExpression(initialExpression);
}

double ExpressionEvaluator::evaluate(const char* expression) {
   
    long double result = 0.0;
    long double currentOperand = 0.0;
    long double decimalMultiplier = 0.1;
    char currentOperator = '+';
    bool inDecimalPart = false;
    int length = std::strlen(expression);

    for (int i = 0; i < length; ++i) {
        if (std::isdigit(expression[i])) {
            if (inDecimalPart) {
                currentOperand += decimalMultiplier * (expression[i] - '0');
                decimalMultiplier *= 0.1;
            }
            else {
                currentOperand = currentOperand * 10 + (expression[i] - '0');
            }
        }
        else if (expression[i] == '.') {
            inDecimalPart = true;
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            result = applyOperator(result, currentOperand, currentOperator);
            currentOperator = expression[i];
            currentOperand = 0.0;
            inDecimalPart = false;
            decimalMultiplier = 0.1;
        }
        else if (expression[i] == '(') {
            int j = findClosingParenthesis(expression, i);
            currentOperand = evaluate(substring(expression, i + 1, j));
            i = j;
        }
    }

    result = applyOperator(result, currentOperand, currentOperator);

    return static_cast<double>(result);
}

double ExpressionEvaluator::evaluate() const {
    return evaluate(expression);
}

char ExpressionEvaluator::operator[](size_t index) const {
    if (index < strlen(expression)) {
        return expression[index];
    }
    else {
        std::cerr << "Index invalid pentru operatorul [].";
        return '\0';
    }
}

void ExpressionEvaluator::setExpression(const char* newExpression) {
    if (isValidExpression(newExpression)) {
        delete[] expression;
        expression = new char[strlen(newExpression) + 1];
        strcpy_s(expression, strlen(newExpression) + 1, newExpression);
    }
    else {
        std::cerr << "Expresia introdusă nu este validă.\n";
    }
}

const char* ExpressionEvaluator::concatenate(const char* expr1, const char* expr2) {
    size_t len1 = std::strlen(expr1);
    size_t len2 = std::strlen(expr2);
    char* result = new char[len1 + len2 + 1];

    strcpy_s(result, len1 + len2 + 1, expr1);
    strcat_s(result, len1 + len2 + 1, expr2);

    return result;
}

const char* ExpressionEvaluator::getExpression() const {
    return expression;
}

ExpressionEvaluator ExpressionEvaluator::operator+(const ExpressionEvaluator& other) const {
    ExpressionEvaluator result;
    result.setExpression(concatenate(expression, other.getExpression()));
    return result;
}

std::istream& operator>>(std::istream& in, ExpressionEvaluator& evaluator) {
    std::cout << "Introduceti expresia pentru ExpressionEvaluator: ";
    char buffer[1000];
    in.getline(buffer, 1000);

    evaluator.setExpressionWithValidation(buffer);
    return in;
}

std::ostream& operator<<(std::ostream& out, const ExpressionEvaluator& evaluator) {
    out << "ExpresieEvaluator: " << evaluator.getExpression();
    return out;
}

double ExpressionEvaluator::applyOperator(double operand1, double operand2, char op) {
    switch (op) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 != 0) {
            return operand1 / operand2;
        }
        else {
            std::cerr << "Nu se poate imparti la zero." << std::endl;
            return 0.0; 
        }
    default:
        std::cerr << "Operator necunoscut: " << op << std::endl;
        return 0.0; 
    }
}

int ExpressionEvaluator::findClosingParenthesis(const char* expression, int startIndex) {
    int count = 1; 
    int i = startIndex + 1;

    while (count > 0 && expression[i] != '\0') {
        if (expression[i] == '(') {
            ++count;
        }
        else if (expression[i] == ')') {
            --count;
        }
        ++i;
    }

    return i - 1; 
}

const char* ExpressionEvaluator::substring(const char* expression, int startIndex, int endIndex) {
    int length = endIndex - startIndex + 1;
    char* sub = new char[length + 1];
    strncpy_s(sub, length + 1, expression + startIndex, length);
    sub[length] = '\0';
    return sub;
}

ExpressionEvaluator::~ExpressionEvaluator() {
    delete[] expression;
}

bool ExpressionEvaluator::isValidExpression(const char* expression) const {
    int openParentheses = 0;

    for (int i = 0; expression[i] != '\0'; ++i) {
        if (expression[i] == '(') {
            openParentheses++;
        }
        else if (expression[i] == ')') {
            openParentheses--;
            if (openParentheses < 0) {
                std::cerr << "Eroare: Paranteze închise fără deschise corespunzătoare." << std::endl;
                return false;
            }
        }
        else if (!std::isdigit(expression[i]) && expression[i] != '.' &&
            expression[i] != '+' && expression[i] != '-' &&
            expression[i] != '*' && expression[i] != '/') {
            std::cerr << "Eroare: Caracter neașteptat în expresie." << std::endl;
            return false;
        }
    }

    if (openParentheses != 0) {
        std::cerr << "Eroare: Paranteze deschise fără închise corespunzătoare." << std::endl;
        return false;
    }

    return true;
}

bool ExpressionEvaluator::setExpressionWithValidation(const char* newExpression) {
    if (isValidExpression(newExpression)) {
        delete[] expression;
        expression = new char[strlen(newExpression) + 1];
        strcpy_s(expression, strlen(newExpression) + 1, newExpression);
        return true;  
    }
    else {
        return false;  
    }
}
