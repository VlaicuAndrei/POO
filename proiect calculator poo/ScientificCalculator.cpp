#include "ExpressionEvaluator.h"
// ScientificCalculator.cpp
#include "ScientificCalculator.h"
#include <iostream>
#include <cmath>

ScientificCalculator::ScientificCalculator() : BasicOperations() {
    
}

ScientificCalculator::ScientificCalculator(const std::string& expr) : BasicOperations(expr) {
    
}

double ScientificCalculator::evaluateExpression() {
    double result = ExpressionEvaluator::evaluate(getExpression().c_str());
    size_t pos = 0;

    
    while ((pos = getExpression().find('^')) != std::string::npos) {
        double base = std::stod(getExpression().substr(0, pos));
        double exponent = std::stod(getExpression().substr(pos + 1));
        result = std::pow(base, exponent);
        setExpression(replaceAtIndex(getExpression(), pos, std::to_string(result)));
    }

    
    while ((pos = getExpression().find('#')) != std::string::npos) {
        double base = std::stod(getExpression().substr(0, pos));
        double order = std::stod(getExpression().substr(pos + 1));
        result = std::pow(base, 1.0 / order);
        setExpression(replaceAtIndex(getExpression(), pos, std::to_string(result)));
    }

    

    return result;
}

std::ostream& operator<<(std::ostream& out, const ScientificCalculator& scientificCalc) {
    out << "ScientificCalculator: Implementati afisarea aici";
    return out;
}

std::istream& operator>>(std::istream& in, ScientificCalculator& scientificCalc) {
    std::cout << "Introduceti date pentru ScientificCalculator: ";
    in >> static_cast<BasicOperations&>(scientificCalc); 
    return in;
}
