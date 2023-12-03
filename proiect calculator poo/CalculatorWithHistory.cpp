// CalculatorWithHistory.cpp
#include "CalculatorWithHistory.h"
#include <iostream>
#include <cstring>

CalculatorWithHistory::CalculatorWithHistory() : ScientificCalculator(), expressionHistory(nullptr) {
    
}

CalculatorWithHistory::CalculatorWithHistory(const std::string& expr) : ScientificCalculator(expr), expressionHistory(nullptr) {
    
}

CalculatorWithHistory::~CalculatorWithHistory() {
    delete[] expressionHistory;
}

double CalculatorWithHistory::evaluateExpression() {
    double result = ScientificCalculator::evaluateExpression();

    
    appendToHistory(getExpression().c_str());

    return result;
}

void CalculatorWithHistory::appendToHistory(const char* expression) {
    if (expressionHistory == nullptr) {
        expressionHistory = new char[strlen(expression) + 1];
        strcpy_s(expressionHistory, strlen(expression) + 1, expression);
    }
    else {
        
        char* newHistory = new char[strlen(expressionHistory) + strlen(expression) + 2];
        strcpy_s(newHistory, strlen(expressionHistory) + 1, expressionHistory);
        strcat_s(newHistory, strlen(expressionHistory) + strlen(expression) + 2, "\n");
        strcat_s(newHistory, strlen(expressionHistory) + strlen(expression) + 2, expression);

        delete[] expressionHistory;
        expressionHistory = newHistory;
    }
}

bool CalculatorWithHistory::operator==(const CalculatorWithHistory& other) const {
    
    if (expressionHistory == nullptr && other.expressionHistory == nullptr) {
        return true; 
    }

    if (expressionHistory == nullptr || other.expressionHistory == nullptr) {
        return false; 
    }

    return std::strcmp(expressionHistory, other.expressionHistory) == 0;
}

bool CalculatorWithHistory::operator!() const {
    
    return expressionHistory == nullptr || expressionHistory[0] == '\0';
}

const char* CalculatorWithHistory::getExpressionHistory() const {
    return expressionHistory;
}

void CalculatorWithHistory::setExpressionHistory(const char* newHistory) {
    if (isValidHistory(newHistory)) {
        delete[] expressionHistory;
        expressionHistory = new char[strlen(newHistory) + 1];
        strcpy_s(expressionHistory, strlen(newHistory) + 1, newHistory);
    }
    else {
        std::cerr << "Istoricul introdus nu este valid.\n";
    }
}

bool CalculatorWithHistory::isValidHistory(const char* history) const {
    while (*history) {
        if (isalnum(*history) || isspace(*history) ||
            *history == '(' || *history == ')' || *history == '[' || *history == ']' ||
            *history == '#' || *history == '^' || *history == '+' || *history == '-' ||
            *history == '*' || *history == '/') {
            ++history;
        }
        else {
            return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const CalculatorWithHistory& calcWithHistory) {
    if (calcWithHistory.getExpressionHistory() != nullptr) {
        out << "Istoricul operatiilor:" << std::endl;
        out << calcWithHistory.getExpressionHistory();
    }
    else {
        out << "Istoricul este gol.";
    }
    return out;
}

std::istream& operator>>(std::istream& in, CalculatorWithHistory& calcWithHistory) {
    std::cout << "Introduceti date pentru CalculatorWithHistory: ";
    in >> static_cast<ScientificCalculator&>(calcWithHistory); 
    return in;
}
