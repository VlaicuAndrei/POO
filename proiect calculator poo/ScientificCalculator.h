// ScientificCalculator.h
#pragma once
#include "BasicOperations.h"

class ScientificCalculator : public BasicOperations {
public:
    ScientificCalculator();
    ScientificCalculator(const std::string& expr);
    double evaluateExpression() override;

    friend std::ostream& operator<<(std::ostream& out, const ScientificCalculator& scientificCalc);
    friend std::istream& operator>>(std::istream& in, ScientificCalculator& scientificCalc);
};
