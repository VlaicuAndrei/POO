// BasicOperations.h
#pragma once
#include "Calculator.h"

class BasicOperations : public Calculator {
public:
    BasicOperations();
    BasicOperations(const std::string& expr);
    double evaluateExpression() override;
    operator double() const;
    friend BasicOperations operator+(const BasicOperations& lhs, const BasicOperations& rhs);
    friend class ScientificCalculator;
    friend std::istream& operator>>(std::istream& in, Calculator& calc);
    friend std::ostream& operator<<(std::ostream& out, const BasicOperations& basicOp);

private:

    std::string replaceAtIndex(const std::string& str, size_t index, const std::string& replacement);
};

