// BasicOperations.cpp
#include "BasicOperations.h"
#include "ExpressionEvaluator.h"
#include <iostream>
#include <cmath>

BasicOperations::BasicOperations() : Calculator() {
    
}


BasicOperations::BasicOperations(const std::string& expr) : Calculator(expr) {
    
}


double BasicOperations::evaluateExpression() {
    std::string currentExpression = getExpression();
    size_t pos = 0;

    try {
        while ((pos = currentExpression.find('^')) != std::string::npos) {
            size_t baseEnd = currentExpression.find_last_not_of("0123456789", pos - 1) + 1;
            double base = std::stod(currentExpression.substr(0, baseEnd));

            size_t powerEnd = currentExpression.find_first_not_of("0123456789", pos + 1);
            double exponent = std::stod(currentExpression.substr(pos + 1, powerEnd - pos - 1));

            double result = std::pow(base, exponent);

            currentExpression.replace(baseEnd, powerEnd - baseEnd + 1, std::to_string(result));
        }

        while ((pos = currentExpression.find('#')) != std::string::npos) {
            size_t baseEnd = currentExpression.find_last_not_of("0123456789", pos - 1) + 1;
            double base = std::stod(currentExpression.substr(0, baseEnd));

            size_t rootEnd = currentExpression.find_first_not_of("0123456789", pos + 1);
            double order = std::stod(currentExpression.substr(pos + 1, rootEnd - pos - 1));

            double result = std::pow(base, 1.0 / order);

            currentExpression.replace(baseEnd, rootEnd - baseEnd + 1, std::to_string(result));
        }

        return ExpressionEvaluator::evaluate(currentExpression.c_str());
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Eroare la evaluarea expresiei: " << e.what() << std::endl;
        return std::numeric_limits<double>::quiet_NaN(); 
    }

    
}


std::istream& operator>>(std::istream& in, BasicOperations& basicOp) {
    std::cout << "Introduceti date pentru BasicOperations: ";
    in >> static_cast<Calculator&>(basicOp); 
    return in;
}

std::ostream& operator<<(std::ostream& out, const BasicOperations& basicOp) {
    out << "BasicOperations: Implementati afisarea aici";
    return out;
}

std::string BasicOperations::replaceAtIndex(const std::string& str, size_t index, const std::string& replacement) {
    std::string result = str;
    result.replace(index, replacement.length(), replacement);
    return result;
}


BasicOperations operator+(const BasicOperations& lhs, const BasicOperations& rhs) {
    BasicOperations result;

    std::string expr1 = lhs.getExpression();
    std::string expr2 = rhs.getExpression();

    std::string resultExpression = expr1 + expr2;

    result.setExpression(resultExpression);

    return result;
}

BasicOperations::operator double() const {
    try {
        return std::stod(getExpression());
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Eroare la conversia implicita la double: " << e.what() << std::endl;
        return std::numeric_limits<double>::quiet_NaN(); 
    }
}
